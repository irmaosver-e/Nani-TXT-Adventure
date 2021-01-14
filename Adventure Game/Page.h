#ifndef PAGE_H
#define PAGE_H

#include <iostream>

class Page
{
public:
	Page();
	~Page();

	void CreateChoices(int numOfChoices);
	void SetChoice(int choiceNumber, int value);
	int GetNumOfChoices();
	int GetChoice(int choiceNum);

	void SetText(std::string text);
	std::string* GetText();

private:
	int m_numOfChoices;
	int* m_choices;
	std::string m_text; 
};

#endif