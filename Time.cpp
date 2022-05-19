#include "Time.h"
#include "utils.h"
using namespace std;
namespace sdds
{

	Time& Time::setToNow()
	{

		m_min = getTime();

		return *this;
	}

	Time::Time(unsigned int min)
	{
		m_min = min;
	}

	std::ostream& Time::write(std::ostream& ostr) const
	{
		int hrs = 0, mins = 0;

		hrs = m_min / 60;
		mins = m_min % 60;

		ostr.setf(ios::fixed);

		if (hrs < 0 && hrs >= 10)
		{

			ostr << hrs;

		}
		else
		{

			ostr.fill('0');
			ostr.width(2);
			ostr << hrs;
			ostr << ":";

		}

		if (mins < 0 && mins >= 10)
		{

			ostr << mins;

		}
		else
		{

			ostr.fill('0');
			ostr.width(2);
			ostr << mins;

		}

		ostr.unsetf(ios::fixed);

		return ostr;

	}



	std::istream& Time::read(std::istream& istr)
	{
		int hrs = 0, mins = 0;
		char getChar = '0';

		istr >> hrs;
		
			istr >> getChar;

			if (getChar == ':')
			{

					istr >> mins;
					m_min = hrs * 60 + mins;
			
			}
			else
			{

				istr.setstate(ios::failbit);

			}
	

		return istr;

	}



	Time& Time::operator-= (const Time& D)
	{
		int hrs = 24 * 60;

		if (m_min <= D.m_min)
		{

			m_min = (m_min + (hrs * ((D.m_min / hrs) + 1))) - D.m_min;

		}
		else
		{

			m_min -= D.m_min;

		}

		return *this;
	}

	Time Time :: operator-(const Time& D)const
	{
		Time M;
		int hrs = 24 * 60;

		if (m_min <= D.m_min)
		{

			M.m_min = (m_min + (hrs * ((D.m_min / hrs) + 1))) - D.m_min;

		}
		else
		{

			M.m_min = m_min - D.m_min;


		}

		return M;

	}

	Time& Time ::operator+=(const Time& D)
	{
		m_min += D.m_min;

		return *this;
	}

	Time Time ::operator+(const Time& D)const
	{
		Time M;

		M.m_min = m_min + D.m_min;

		return M;
	}

	Time& Time ::operator=(unsigned int val)
	{
		m_min = val;

		return *this;
	}

	Time& Time :: operator*=(unsigned int val)
	{
		m_min *= val;

		return *this;
	}

	Time Time :: operator*(unsigned int val)const
	{
		Time M;

		M.m_min = m_min * val;

		return M;
	}

	Time& Time :: operator/= (unsigned int val)
	{
		m_min /= val;

		return *this;
	}

	Time Time :: operator/(unsigned int val)const
	{
		Time M;

		M.m_min = m_min / val;

		return M;
	}

	Time :: operator int()const
	{
		return m_min;
	}

	Time::operator unsigned int()const
	{
		return m_min;
	}

	std::ostream& operator<<(std::ostream& ostr, const Time& D)
	{
		D.write(ostr);

		return ostr;
	}

	std::istream& operator>>(std::istream& istr, Time& D)
	{
		D.read(istr);

		return istr;
	}
}