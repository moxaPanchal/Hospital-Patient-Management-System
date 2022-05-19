#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <cstring>
#include "utils.h"
#include "Time.h"
using namespace std;
namespace sdds
{
	bool debug = false;  // made global in utils.h
	int getTime()
	{
		int mins = -1;
		if (debug)
		{
			Time t(0);
			cout << "Enter current time: ";
			do
			{
				cin.clear();
				cin >> t;   // needs extraction operator overloaded for Time
				if (!cin)
				{
					cout << "Invlid time, try agian (HH:MM): ";
					cin.clear();
				}
				else
				{
					mins = int(t);
				}
				cin.ignore(1000, '\n');
			} while (mins < 0);
		}
		else
		{
			time_t t = time(NULL);
			tm lt = *localtime(&t);
			mins = lt.tm_hour * 60 + lt.tm_min;
		}
		return mins;
	}

	int getInt(const char* prompt)
	{
		int value = 0;
		char getChar = 0;
		bool ok = true;

		if (prompt)
		{
			cout << prompt;
		}

		do
		{
			ok = false;

			cin >> value;

			if (cin.fail())
			{

				cout << "Bad integer value, try again: ";
				cin.clear();
				cin.ignore(10000, '\n');

				ok = true;

			}
			else
			{

				getChar = cin.get();

				if (getChar != '\n')
				{

					cout << "Enter only an integer, try again: ";
					cin.clear();
					cin.ignore(10000, '\n');

					ok = true;

				}

			}

		} while (ok);

		return value;

	}

	int getInt(int min, int max, const char* prompt, const char* errorMessage, bool showRangeAtError)
	{
		int value = 0;
		bool ok = false;

		if (prompt)
		{
			cout << prompt;
		}

		do
		{

			value = getInt();

			if (value >= min && value <= max)
			{

				ok = true;

			}
			else if (errorMessage != nullptr)
			{

				if (showRangeAtError == true)
				{

					cout << errorMessage << "[" << min;
					cout << " <= value <= " << max << "]: ";

				}
				else
				{

					cout << errorMessage;

				}

			}

		} while (!ok);

		return value;
	}

	char* getcstr(const char* prompt, std::istream& istr, char delimiter)
	{

		char getString1[10000];
		char* getString2;

		if (prompt)
		{

			cout << prompt;

		}

		istr.getline(getString1, 10000, delimiter);

		getString2 = new char[strlen(getString1) + 1];

		strcpy(getString2, getString1);

		return getString2;

	}

}