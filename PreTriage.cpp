#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <fstream>
#include "PreTriage.h"
#include "CovidPatient.h"
#include "TriagePatient.h"
#include "utils.h"


using namespace std;
namespace sdds
{

	PreTriage::PreTriage(const char* dataFileName) :m_averCovidWait(15), m_averTriageWait(5),m_appMenu("General Hospital Pre-Triage Application\n1- Register\n2- Admit", 2), m_pMenu("Select Type of Admittance:\n1- Covid Test\n2- Triage", 2)
	{

		m_dataFilename = new char[strlen(dataFileName) + 1];
		strcpy(m_dataFilename, dataFileName);

		PreTriage::load();

	}

	PreTriage::~PreTriage()
	{

		int i = 0;
		ofstream open(m_dataFilename);

		if (open)
		{

			cout << "Saving Average Wait Times," << endl;
			cout << "   COVID TEST: " << m_averCovidWait << endl;
			cout << "   Triage: " << m_averTriageWait << endl;

			open << m_averCovidWait << ",";
			open << m_averTriageWait << endl;

			cout << "Saving m_lineup..." << endl;

			for (i = 0; i < m_lineupSize; i++)
			{

				cout << i + 1;
				cout << "- ";

				m_lineup[i]->csvWrite(cout) << endl;
				m_lineup[i]->csvWrite(open) << endl;

			}

			for (i = 0; i < m_lineupSize; i++)
			{

				delete m_lineup[i];

			}

			delete[] m_dataFilename;
			m_dataFilename = nullptr;

			cout << "done!" << endl;

		}

	}

	const Time PreTriage::getWaitTime(const Patient& p) const
	{

		int i = 0;
		unsigned int countPatients = 0;
		Time estimatedTime;

		for (i = 0; i < m_lineupSize; i++)
		{

			if (m_lineup[i]->type() == p.type())
			{

				countPatients++;

			}

		}

		estimatedTime = Time(p) * countPatients;

		return estimatedTime;

	}

	void PreTriage::setAverageWaitTime(const Patient& p)
	{

		Time currentTime;
		currentTime = Time(getTime());

		Time patientTime = Time(p);

		unsigned int p_ticketNo = p.number();

		if (p.type() == 'T')
		{

			m_averTriageWait = ((currentTime - patientTime) + (m_averTriageWait * (p_ticketNo - 1))) / p_ticketNo;

		}
		else
		{

			m_averCovidWait = ((currentTime - patientTime) + (m_averCovidWait * (p_ticketNo - 1))) / p_ticketNo;

		}

	}

	void PreTriage::removePatientFromLineup(int index)
	{

		removeDynamicElement(m_lineup, index, m_lineupSize);

	}

	int PreTriage::indexOfFirstInLine(char type) const
	{

		int i = 0;
		int value = -1;
		int keepRepeating = 1;

		for (i = 0; i < m_lineupSize && keepRepeating; i++)
		{

			if (m_lineup[i]->type() == type)
			{
				keepRepeating = 0;
				value = i;
			}

		}

		return value;

	}

	void PreTriage::load()
	{

		int i = 0;
		bool keepRepeating = true;
		char getChar = 0;
		Patient* patientPtr = nullptr;

		ifstream open(m_dataFilename);

		if (open)
		{
			cout << "Loading data..." << endl;

			open >> m_averCovidWait;
			open.ignore(1000, ',');

			open >> m_averTriageWait;
			open.ignore(1000, '\n');

			for (i = 0; i < maxNoOfPatients && keepRepeating; i++)
			{

				getChar = open.get();
				open.ignore(1000, ',');

				if (open.fail() == true)
				{

					keepRepeating = false;

				}
				else
				{

					keepRepeating = true;

				}

				if (getChar == 'T')
				{

					patientPtr = new TriagePatient();


				}
				else if (getChar == 'C')
				{

					patientPtr = new CovidPatient();

				}
				else
				{

					patientPtr = nullptr;

				}

				if (patientPtr != nullptr)
				{

					patientPtr->fileIO(true);
					open >> *patientPtr;
					patientPtr->fileIO(false);

					m_lineup[i] = patientPtr;
					m_lineupSize++;

				}

			}

			if (open)
			{

				cout << "Warning: number of records exceeded " << maxNoOfPatients << endl;

			}

			if (m_lineupSize == 0)
			{

				cout << "No data or bad data file!" << endl;

			}
			else
			{

				cout << m_lineupSize;
				cout << " Records imported..." << endl;

			}

			cout << endl;

		}

	}

	void PreTriage::reg()
	{
		int option = 0;

		if (m_lineupSize == maxNoOfPatients)
		{

			cout << "Line up full!" << endl;

		}
		else
		{

			m_pMenu >> option;

			switch (option)
			{
			case 1:

				m_lineup[m_lineupSize] = new CovidPatient();

				break;

			case 2:

				m_lineup[m_lineupSize] = new TriagePatient();

				break;

			case 0:

				break;

			}


			m_lineup[m_lineupSize]->setArrivalTime();

			cout << "Please enter patient information: " << endl;
			m_lineup[m_lineupSize]->fileIO(false);
			m_lineup[m_lineupSize]->read(cin);
			cout << endl;
			
			cout << "******************************************" << endl;
			m_lineup[m_lineupSize]->write(cout);
			cout << "Estimated Wait Time: ";
			cout << getWaitTime(*m_lineup[m_lineupSize]) << endl;
			cout << "******************************************" << endl << endl;

			m_lineupSize++;

		}
	}

	void PreTriage::admit()
	{

		int option = 0;
		int next_patient = 0;
		m_pMenu >> option;

		switch (option)
		{

		case 1:
			
			next_patient = indexOfFirstInLine('C');
			
			break;
		
		case 2:
		
			next_patient = indexOfFirstInLine('T');
			
			break;
		
		case 0:
		
			break;
		
		}
		

		if (next_patient != -1)
		{

			cout << endl;
			cout << "******************************************" << endl;
			m_lineup[next_patient]->fileIO(false);
			cout << "Calling for ";
			m_lineup[next_patient]->write(cout);
			cout << "******************************************" << endl << endl;
			
			setAverageWaitTime(*m_lineup[next_patient]);
			removePatientFromLineup(next_patient);

		}
		else
		{

			return;
			
		}

	}


	void PreTriage::run()
	{
		int option = 0;
		bool validation = true;

		do
		{

			m_appMenu >> option;

			switch (option)
			{

			case 1:
			
				reg();
				
				break;
			
			case 2:
			
				admit();
				
				break;
			
			case 0:
			
				validation = false;
				
				break;
			
			}

		} while (validation);
	}


}