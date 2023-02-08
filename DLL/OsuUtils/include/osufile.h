#ifndef _OSU_FILE_H
#define _OSU_FILE_H

#include <cstdint>
#include <fstream>
#include <iostream>
#include "dlldef.h"

#define MAX_FILE_BUFFER 8192
#define OSU_STR_PRESENT 0x0b

typedef unsigned char byte_t;
typedef int16_t short_t;
typedef int32_t int_t;
typedef int64_t long_t;
typedef unsigned long ULEB128_t;
typedef char* str_t;

namespace Osu
{
	/**
	* Class used for loading osu filetypes
	*/
	class OsuFile
	{
	public:
		OsuFile(const char* filePath);
		~OsuFile();
		void Close();

		/**
		* Load primitive datatype from input buffer
		*
		* @param dest - Destination to read value to
		*/
		template <typename T>
		void ReadType(T& dest)
		{
#ifdef OSUUTILS_VERBOSE
			std::cout << "Reading new type" << std::endl;
#endif
			// wacky reinterpret pointer stuff
			dest = *(T*)(this->inputStream + this->cPtr);
			this->cPtr += sizeof(T);
#ifdef OSUUTILS_VERBOSE
			std::cout << "Read: " << dest << std::endl;
#endif
		}

		/**
		* Load unsigned LEB128 from input buffer
		*
		* @param dest - Destination to read value to
		*/
		void ReadULEB128(ULEB128_t& dest);

		/**
		* Load string from input buffer
		*
		* @param dest - Destination to read value to
		*/
		void ReadString(str_t& dest);

		/**
		* Read LZMA string from file
		* 
		* @param dest - Destination to read value to
		*/
		void ReadLzma(str_t& dest);

	private:
		unsigned long cPtr;
		char* inputStream;
		std::ifstream *inputFile;
		unsigned long readBytes{ 0 };
		unsigned long initialSize{ 0 };
		bool isOpen{ false };

		/**
		* Load the correct amount of bytes into the file buffer
		*
		* @param byteOffset - x amount of offset from the front of the buffer to load to
		*/
		void LoadBytes(int byteOffset = 0);

		/**
		* Check if the given size can be loaded from the remaining bytes
		*
		* @param size - size of type being loaded
		*/
		void CheckSize(size_t size);
	};
}

#endif