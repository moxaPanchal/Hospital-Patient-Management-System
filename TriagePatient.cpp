#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "TriagePatient.h"


using namespace std;

namespace sdds
{

	int nextTriageTicket = 1;
	TriagePatient::TriagePatient() :Patient(nextTriageTicket)
	{

		triageSymp = nullptr;
		nextTriageTicket += 1;

	}


	char TriagePatient::type() const
	{
		return 'T';
	}


	std::ostream& TriagePatient::csvWrite(std::ostream& ostr) const
	{

		Patient::csvWrite(ostr);
		ostr << "," << triageSymp;

		return ostr;

	}


	std::istream& TriagePatient::csvRead(std::istream& istr)
	{

		char symp[1000] = { 0 };

		delete[] triageSymp;
		triageSymp = nullptr;

		Patient::csvRead(istr);
		istr.ignore(1000, ',');

		istr.getline(symp, 1000, '\n');

		triageSymp = new char[strlen(symp) + 1];
		strcpy(triageSymp, symp);

		nextTriageTicket = number() + 1;

		return istr;

	}

	std::ostream& TriagePatient::write(std::ostream& ostr)const
	{

		if (fileIO())
		{

			csvWrite(ostr);

		}
		else
		{

			ostr << "TRIAGE";
			cout << endl;
			Patient::write(ostr);
			cout << endl;
			ostr << "Symptoms: ";
			cout << triageSymp << endl;

		}

		return ostr;

	}

	std::istream& TriagePatient::read(std::istream& istr)
	{

		if (fileIO())
		{

			csvRead(istr);
		
		}
		else
		{

			char symp[1000] = { 0 };
			
			delete[] triageSymp;
			triageSymp = nullptr;

			Patient::read(istr);
			cout << "Symptoms: ";

			istr.getline(symp, 1000, '\n');
			
			triageSymp = new char[strlen(symp) + 1];
			strcpy(triageSymp, symp);

		}

		return istr;

	}

	TriagePatient::~TriagePatient()
	{
		delete[] triageSymp;
		triageSymp = nullptr;
	}

}