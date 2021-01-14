#include "Game.h"
#include <conio.h>

Game::Game()
{
	m_fR.LoadFile("Adventure Game.txt");
	CreatePages();

	m_print = true;
	m_currentPage = 0;
}

Game::~Game()
{
	DeletePages();
}

void Game::Run()
{
	char key = ' ';

	while(key != 'q')
	{
		while(!GetInput(&key))
		{
			if(m_print)
				PrintPage();
		}

		FindPage(&key);
	}
}

bool Game::GetInput(char *c)
{
	if(_kbhit())
	{
		*c = _getch();
		return true;
	}

	return false;
}

void Game::CreatePages()
{	
	m_pages = new Page[FindNumOfPages()];

	SeparateBookIntoPages();
}

void Game::DeletePages()
{
	delete[] m_pages;
}

void Game::PrintPage()
{
	std::cout << "\nChoose an option or press Q to exit!\n\n";

	std::string str = *(m_pages[m_currentPage].GetText());
	std::cout << str.c_str();

	m_print = false;
}

void Game::FindPage(char* key)
{
	int keyValue = (*key) - 'a';

	if(keyValue >= 0 && keyValue < m_pages[m_currentPage].GetNumOfChoices())
	{
		m_currentPage = (m_pages[m_currentPage].GetChoice(keyValue)) - 1;
		m_print = true;
	}
}

int Game::FindNumOfPages()
{
	int numOfPages = 0;

	std::string book = m_fR.GetBuffer();

	std::string::size_type searchFrom = 0;
	
	while((searchFrom = book.find("#page",searchFrom)) != std::string::npos)
	{
		searchFrom++;
		numOfPages++;
	}

	return numOfPages;
}

void Game::SeparateBookIntoPages()
{
	//gets the buffer and stores it into a string for comparisons
	std::string book = m_fR.GetBuffer();

	//will store relative positions in the string for searches
	std::string::size_type searchPos = 0;
	std::string::size_type tempPos = 0;
	
	//keeps track of the page number
	int pageNum = 0;
	
	//loops until the end of the book
	while(searchPos != std::string::npos)
	{
		//finds a page
		if(book.find("#page ", searchPos))
		{
			//realigns the search allocator to the beggining of the text
			searchPos = book.find("\n", searchPos) + 1;
		
			//realigns the temp allocator to the end of the text
			tempPos = book.find("#choices#",searchPos);
	
			//gets the text and passes to the page
			std::string text = book.substr(searchPos,(tempPos - searchPos));
			m_pages[pageNum].SetText(text);


			//realigns the search allocator to the beggining of the choices
			searchPos = book.find("\n",tempPos) +1;
			//realigns the temp allocator to the end of the choices
			tempPos = book.find("#endpage#",searchPos);
			
			//stores the choices
			std::string choices = book.substr(searchPos,(tempPos - searchPos));

			//finds number of choices
			int numOfChoices = 0;
			while(searchPos != tempPos)
			{
				if(IsAnum(book[searchPos]))
				{
					//checks for 2 digit choices
					if(IsAnum(book[searchPos+1]))
						searchPos++;

					numOfChoices++;
				}

				searchPos++;
			}

			//creates the choices
			if(numOfChoices > 0)
				m_pages[pageNum].CreateChoices(numOfChoices);

			//populates the choices
			int choice = 0;
			int choiceValue = 0;
			for(unsigned int i = 0; i < choices.length(); i++)
			{
				if(IsAnum(choices[i]))
				{
					if(i+1 < choices.length() && IsAnum(choices[i+1]))
					{
						choiceValue = (choices[i+1] - '0') + (choices[i] - '0') * 10;
						i++;
					}
					else
						choiceValue = (choices[i] - '0');

					m_pages[pageNum].SetChoice(choice, choiceValue);
					choice++;
				}
			}

			//realigns the search allocator to the beggining of the new page
			searchPos = book.find("#page ", searchPos);

			//increase the page number
			pageNum++;
		}
		else
			searchPos++;
	}
}

bool Game::IsAnum(char c)
{
	//checks if char is a number
	if(c >= '0' && c <= '9')
	{
		return true;
	}

	return false;
}
