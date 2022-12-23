#include "..\include\osufile.h"

Osu::OsuFile::OsuFile(const char* filePath)
{
	this->inputFile = new std::ifstream(filePath, std::ios_base::in | std::ios_base::binary);
	if (!this->inputFile->fail())
		this->isOpen = true;
}

void Osu::OsuFile::Close()
{
	if (this->isOpen)
	{
		// delete input char buffer
		delete[] this->inputStream;
		// close input stream
		this->inputFile->close();
		delete this->inputFile;
		this->isOpen = false;
	}

}

Osu::OsuFile::~OsuFile()
{
	// Call the close method if not already called
	this->Close();
}

void Osu::OsuFile::LoadBytes(int byteOffset)
{
	// if initial size has not yet been determined
	if (!this->initialSize)
	{
		// go to end of file, get bytes and then set initial size
		this->inputFile->seekg(0, std::ios::end);
		size_t sizeLeft = this->inputFile->tellg();
		this->inputFile->seekg(0, std::ios::beg);
		this->initialSize = sizeLeft;
	}
	// bytes left in file
	size_t bytesLeft = this->initialSize - this->readBytes;
	// accounting for byte offset meaning slightly less bytes can be read
	int maxBufferSize = MAX_FILE_BUFFER - byteOffset;
	// set the length to read to either MAX_FILE_BUFFER - offset or simply to the amount of bytes left
	int length = maxBufferSize * (maxBufferSize <= bytesLeft) + bytesLeft * (bytesLeft < maxBufferSize);
	// read amount of bytes and add to length
	this->inputFile->read(&this->inputStream[byteOffset], length);
	this->readBytes += length;
}

void Osu::OsuFile::CheckSize(size_t size)
{
	// bytes left in current buffer
	unsigned long bytesLeft = MAX_FILE_BUFFER - this->readBytes;
	// if there are less bytes left than bytes in object
	if (bytesLeft < size)
	{
		// copy the last x bits to the start of the file
		memcpy_s(this->inputStream, bytesLeft, &this->inputStream[this->cPtr], bytesLeft);
		// set cPtr to 0 and load bytes from the byte offset
		this->cPtr = 0;
		this->LoadBytes(bytesLeft);
	}
}

void Osu::OsuFile::ReadULEB128(ULEB128_t& dest) {
	ULEB128_t result = 0;
	int shift = 0;
	int count = 0;

	while (1) {
		byte_t tempByte;
		this->ReadType<byte_t>(tempByte);
		count++;
		result |= (tempByte & 0x7f) << shift;
		shift += 7;

		if (!(tempByte & 0x80)) break;
	}
	cPtr += count;
}

void Osu::OsuFile::ReadString(str_t& dest)
{
	byte_t isPresent;
	this->ReadType<byte_t>(isPresent);
	if (isPresent == OSU_STR_PRESENT)
	{
		ULEB128_t stringSize;
		this->ReadULEB128(stringSize);
		dest = new char[stringSize + 1]();
		memcpy_s(dest, stringSize + 1, &this->inputStream[this->cPtr], stringSize);
		this->cPtr += stringSize;
	}
}