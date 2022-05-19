#include <iostream>
#include "CovidPatient.h"

using namespace std;

namespace sdds
{

	int nextCovidTicket = 1;
	CovidPatient::CovidPatient() :Patient(nextCovidTicket)
	{ 

		nextCovidTicket += 1;
	
	}

	char CovidPatient::type()const
	{

		return 'C';
	
	}

	std::istream& CovidPatient::csvRead(std::istream& istr)
	{

		Patient::csvRead(istr);

		nextCovidTicket = number() + 1;

		istr.ignore(1000, '\n');
		
		return istr;
	
	}

	std::ostream& CovidPatient::write(std::ostream& ostr)const
	{

		if (fileIO() == true)
		{

			Patient::csvWrite(ostr);
		
		}
		else
		{

			ostr << "COVID TEST" << endl;
			Patient::write(ostr) << endl;

		}

		return ostr;

	}

	std::istream& CovidPatient::read(std::istream& istr)
	{

		if (fileIO() == true)
		{

			csvRead(istr);
		
		}
		else
		{

			Patient::read(istr);
		
		}

		return istr;
	
	}


}


