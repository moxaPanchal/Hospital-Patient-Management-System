#define _CRT_SECURE_NO_WARNINGS
#include "Menu.h"
#include <cstring>
#include "utils.h"

using namespace std;
namespace sdds
{
	Menu::Menu(const char* MenuContent, int NoOfSelections)
	{

		m_text = new char[strlen(MenuContent) + 1];
		strcpy(m_text, MenuContent);
		m_noOfSel = NoOfSelections;
	}

	Menu:: ~Menu()
	{
		delete[] m_text;
		m_text = nullptr;
	}

	Menu::Menu(const Menu& M)
	{

		if (M.m_text != nullptr && M.m_noOfSel != 0)
		{
			m_text = new char[strlen(M.m_text) + 1];
			strcpy(m_text, M.m_text);
			m_noOfSel = M.m_noOfSel;
		}
	}

	Menu& Menu::operator=(const Menu& M)
	{
		if (M.m_text != nullptr && M.m_noOfSel != 0)
		{
			delete[] m_text;
			m_text = nullptr;

			m_text = new char[strlen(M.m_text) + 1];
			strcpy(m_text, M.m_text);
			m_noOfSel = M.m_noOfSel;
		}

		return *this;
	}

	void Menu::display()const
	{
		cout << m_text << endl;
		cout << "0- Exit" << endl;
	}

	int& Menu::operator>>(int& Selection)
	{
		int select = 0;
		display();
		select= getInt(0, m_noOfSel, "> ", "Invalid option ", true);
		Selection = select;
		return Selection;
	}


}