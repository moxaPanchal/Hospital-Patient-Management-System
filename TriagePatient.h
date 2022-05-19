#ifndef SDDS_TRIAGEPATIENT_H_
#define SDDS_TRIAGEPATIENT_H_

#include<iostream>
#include "Patient.h"

namespace sdds
{
	class TriagePatient :public Patient
	{

		char* triageSymp;
	
	public:
		
		TriagePatient();
		
		virtual char type() const;
		virtual std::ostream& csvWrite(std::ostream& ostr)const;
		virtual std::ostream& write(std::ostream& ostr)const;

		virtual std::istream& csvRead(std::istream& istr);
		virtual std::istream& read(std::istream& istr);
		
		~TriagePatient();

	};
}

#endif
