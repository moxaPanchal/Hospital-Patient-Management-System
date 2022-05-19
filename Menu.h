#ifndef SDDS_MENU_H
#define SDDS_MENU_H

namespace sdds
{


	class Menu
	{
		char* m_text = nullptr; // holds the menu content dynamically
		int m_noOfSel = 0;  // holds the number of options displayed in menu content
		void display()const;
	public:
		Menu(const char* MenuContent, int NoOfSelections);
		virtual ~Menu();
		int& operator>>(int& Selection);
		Menu(const Menu& M);
		Menu& operator=(const Menu& M);
	};

}
#endif
