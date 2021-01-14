#ifndef GAME_H
#define GAME_H

#include "FileReader.h"
#include "Page.h"

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	bool GetInput(char *c);

	void CreatePages();
	void DeletePages();
	void PrintPage();
	void FindPage(char* key);

	int FindNumOfPages();
	void SeparateBookIntoPages();
	bool IsAnum(char c);
	
	bool m_print;
	int m_currentPage;

	FileReader m_fR;
	Page* m_pages;
};

#endif