#ifndef FILE_READER_H
#define FILE_READER_H

class FileReader
{
public:
	~FileReader();

	void LoadFile(char* fileName);
	char* GetBuffer();

private:
	char* m_buffer;
};

#endif