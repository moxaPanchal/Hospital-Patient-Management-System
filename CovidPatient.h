#ifndef SDDS_COVIDPATIENT_H_
#define SDDS_COVIDPATIENT_H_

#include "Patient.h"

namespace sdds
{

	class CovidPatient :public Patient
	{

	public:

		CovidPatient();
	
		virtual char type()const;
		
		virtual std::istream& csvRead(std::istream& istr);
		virtual std::istream& read(std::istream& istr);

		virtual std::ostream& write(std::ostream& ostr)const;

	};

}


#endif