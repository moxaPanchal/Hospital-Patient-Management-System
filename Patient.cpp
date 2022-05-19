#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Patient.h"
#include "utils.h"
using namespace std;

namespace sdds
{
	Patient::Patient(int ticketNo, bool fileSuccess) : tick(ticketNo)
	{
		fileOk = fileSuccess;
	}

	bool Patient::fileIO() const
	{
		return fileOk;
	}

	void Patient::fileIO(bool fileSuccess)
	{
		fileOk = fileSuccess;
	}

	bool Patient::operator==(char compType) const
	{
		bool check = false;

		if (type() == compType)
		{
			check = true;
		}
		else
		{
			check = false;
		}

		return check;
	}
	bool Patient::operator==(const Patient& Pat) const
	{
		bool check = false;

		if (type() == Pat.type())
		{
			check = true;
		}
		else
		{
			check = false;
		}
	

		return check;
	}

	void Patient::setArrivalTime()
	{
		tick.resetTime();
	}

	Patient::operator Time() const
	{
		return Time(tick);
	}

	int Patient::number() const
	{
		return tick.number();
	}

	std::istream& Patient::csvRead(std::istream& istr)
	{
		char storeName[1000];

		delete[] patient_name;
		patient_name = nullptr;

		istr.get(storeName, 1000, ',');

		patient_name = new char[strlen(storeName) + 1];
		strcpy(patient_name, storeName);
		istr.ignore(1000, ',');

		istr >> ohipNumber;
		istr.ignore(1000, ',');

		return tick.csvRead(istr);
	}

	std::ostream& Patient::csvWrite(std::ostream& ostr) const
	{
		ostr << type() << "," << patient_name;
		ostr << "," << ohipNumber << ",";

		tick.csvWrite(ostr);

		return ostr;
	}
	std::ostream& Patient::write(std::ostream& ostr) const
	{
		char storeName[26];

		strncpy(storeName, patient_name, 25);
		storeName[25] = 0;

		ostr << tick << endl;

		ostr << storeName << ", OHIP: " << ohipNumber;
		return ostr;
	}

	std::istream& Patient::read(std::istream& istr)
	{
		char storeName[1000] = { 0 };

		delete[] patient_name;
		patient_name = nullptr;

		cout << "Name: ";

		istr.get(storeName, 1000, '\n');

		patient_name = new char[strlen(storeName) + 1];
		strcpy(patient_name, storeName);

		istr.ignore(1000, '\n');

		cout << "OHIP: ";
		ohipNumber = getInt(100000000, 999999999, nullptr, "Invalid OHIP Number, ", true);

		return istr;
	}


	Patient::~Patient()
	{
		delete[] patient_name;
		patient_name = nullptr;
	}

}