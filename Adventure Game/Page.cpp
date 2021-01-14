#include "Page.h"

Page::Page()
{
	m_choices = NULL;
	m_text = "";
	m_numOfChoices = 0;
}

Page::~Page()
{
	delete[] m_choices;
}

void Page::CreateChoices(int numOfChoices)
{
	m_choices = new int[numOfChoices];
	m_numOfChoices = numOfChoices;
}

void Page::SetChoice(int choiceNumber, int value)
{
	m_choices[choiceNumber] = value;
}

int Page::GetNumOfChoices()
{
	return m_numOfChoices;
}

int Page::GetChoice(int choiceNum)
{
	return m_choices[choiceNum];
}

void Page::SetText(std::string text)
{
	m_text = text;
}

std::string* Page::GetText()
{
	return &m_text;
}