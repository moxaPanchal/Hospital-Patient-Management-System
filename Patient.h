#ifndef _SDDS_PATIENT_H
#define _SDDS_PATIENT_H

#include "IOAble.h"
#include "Ticket.h"

namespace sdds
{
	class Patient :public IOAble
	{
		char* patient_name=nullptr;
		int ohipNumber = 0;
		Ticket tick;
		bool fileOk = false;

	public:
		Patient(int ticketNo = 0, bool fileSuccess = false);
		virtual ~Patient();
	
		Patient(const Patient&) = delete;
		Patient& operator=(const Patient&) = delete;

		virtual char type()const = 0;
		bool fileIO()const;
		void fileIO(bool fileSuccess);


		bool operator==(char compType) const;
		bool operator==(const Patient&) const;

		void setArrivalTime();
		operator Time()const;
		
		int number()const;

		std::ostream& csvWrite(std::ostream& ostr)const;
		std::istream& csvRead(std::istream& istr);

		std::ostream& write(std::ostream& ostr)const;
		std::istream& read(std::istream& istr);
	};


}

#endif