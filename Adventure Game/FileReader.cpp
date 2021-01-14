#include "FileReader.h"
#include <fstream>

FileReader::~FileReader()
{
	delete[] m_buffer;
}

void FileReader::LoadFile(char* fileName)
{
	std::ifstream myStream (fileName, std::ifstream::binary);

	if (myStream)
	{
		// get length of file:
		myStream.seekg (0, myStream.end);
		int length = (int)myStream.tellg();
		myStream.seekg (0, myStream.beg);

		m_buffer = new char [length + 1];

		// read data as a block:
		myStream.read (m_buffer,length);

		//writes the end character
		m_buffer[length] = '\0';

		myStream.close();
	}
}

char* FileReader::GetBuffer()
{
	return m_buffer;
}