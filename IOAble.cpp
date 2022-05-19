#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include "IOAble.h"
using namespace std;
namespace sdds
{

	std::ostream& IOAble::csvWrite(std::ostream& ostr)const
	{
		return ostr;
	}

	std::istream& IOAble::csvRead(std::istream& istr)
	{
		return istr;
	}

	std::ostream& IOAble::write(std::ostream& ostr)const
	{
		return ostr;
	}

	std::istream& IOAble::read(std::istream& istr)
	{
		return istr;
	}

	IOAble:: ~IOAble()
	{
		;
	}

	std::ostream& operator<<(std::ostream& ostr, const IOAble& I)
	{
		I.write(ostr);
		return ostr;
	}
	
	std::istream& operator>>(std::istream& istr, IOAble& I)
	{
		I.read(istr);
		return istr;
	}


}