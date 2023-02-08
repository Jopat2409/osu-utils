#include "..\include\osufile.h"
#include <iostream>
#include <assert.h>
#include "..\include\lzma.h"

Osu::OsuFile::OsuFile(const char* filePath)
{
	this->inputFile = new std::ifstream(filePath, std::ios_base::in | std::ios_base::binary);
#ifdef OSUUTILS_VERBOSE
	std::cout << "Successfully loaded new file!";
#endif
	this->LoadBytes();
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
		// initialise input stream
		this->inputStream = new char[MAX_FILE_BUFFER]();
	}
	// bytes left in file
	size_t bytesLeft = this->initialSize - this->readBytes;
	// accounting for byte offset meaning slightly less bytes can be read
	int maxBufferSize = MAX_FILE_BUFFER - byteOffset;
	// set the length to read to either MAX_FILE_BUFFER - offset or simply to the amount of bytes left
	int length = maxBufferSize * (maxBufferSize <= bytesLeft) + bytesLeft * (bytesLeft < maxBufferSize);
#ifdef OSUUTILS_VERBOSE
	std::cout << "Attempting to read " << length << "bytes" << std::endl;
#endif
	// read amount of bytes and add to length
	this->inputFile->read(&this->inputStream[byteOffset], length);
	this->readBytes += length;
}

void Osu::OsuFile::CheckSize(size_t size)
{
	// bytes left in current buffer
	unsigned long bytesLeft = MAX_FILE_BUFFER - this->cPtr;
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
		result |= (tempByte & 0x7f) << shift;
		shift += 7;

		if (!(tempByte & 0x80)) break;
	}
	dest = result;
#ifdef OSUUTILS_VERBOSE
	std::cout << "Read ULEB128 " << dest << std::endl;
#endif
}

void Osu::OsuFile::ReadString(str_t& dest)
{
	byte_t isPresent;
	this->ReadType<byte_t>(isPresent);
	if (isPresent == OSU_STR_PRESENT)
	{
		ULEB128_t stringSize;
		this->ReadULEB128(stringSize);
		this->CheckSize(stringSize);
		dest = new char[stringSize + 1]();
		memcpy_s(dest, stringSize + 1, this->inputStream + this->cPtr, stringSize);
		this->cPtr += stringSize;
#ifdef OSUUTILS_VERBOSE
		std::cout << "Read string " << dest << std::endl;
#endif
	}
}

void Osu::OsuFile::ReadLzma(str_t& dest)
{
	// This method SCREAMS memory leakage sadge
	int_t size;
	this->ReadType<int_t>(size);
	size -= 33;
#ifdef OSUUTILS_VERBOSE
	std::cout << "LZMA SIZE: " << size << std::endl;
#endif
	int16_t prob = LZMA_PROB_START;
	int32_t range = LZMA_RANGE_START;
	cPtr += 1;
	int32_t code;
	this->ReadType<int32_t>(code);
	char readByte;
	int readBytes = 0;
	int cInd = 0;
	char* finalData = new char[size]();
	while (size > readBytes)
	{
		if (range < LZMA_RANGE_THRESH)
		{
			range = range << 8;
			code = code << 8;
			this->ReadType<char>(readByte);
			readBytes += 1;
			code |= readByte;
		}
		range = range / 2;
		if (code < range)
		{
			finalData[cInd] = 0;
			cInd += 1;
		}
		else {
			code = code - range;
			finalData[cInd] = 1;
			cInd += 1;
		}
		if (cInd >= size)
		{
			char* tempData = finalData;
			finalData = new char[size * 2]();
			memcpy_s(finalData, size, tempData, size);
			delete[] tempData;
		}
	}
	dest = new char[size];
	memcpy_s(dest, size, finalData , size);
	delete[] finalData;
}