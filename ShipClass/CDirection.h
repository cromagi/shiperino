//----------------------------------------------------------------------------
//	File:			CDirection.h
//
//	Class:			CDirection
//----------------------------------------------------------------------------
#ifndef CDirection_H
#define CDirection_H
#include <iostream>
#include <string>
#include <stdio.h>
#include <exception>
#include <stdexcept>
#include "safeio.h"
using namespace std;
//enumerated type for class
enum Direction
{
	HORIZONTAL, // 0
	VERTICAL	// 1
};

namespace P4_CSinkFleet
{
	using namespace std;
	//------------------------------------------------------------------------
	//	Title:			Cell Direction Class
	//
	//	Description:	This class allows the proper input of direction.
	//
	//	Programmers:	
	//
	//	Date:		
	//
	//	Version:	
	//
	//	Environment:	
	//			
	//			
	//
	//	Class CDirection:
	//
	//	Properties:
	//					Direction m_direction, -- 0 if Horizontal and 
	//						1 if Vertical
	//
	//	Methods:
	//		Inline:
	//					operator Direction()const -- accessor
	//							Returns: m_direction
	//
	//		Non-inline:
	//
	//			CDirection(int ship = 0)
	//				Default constructor
	//				Initializes m_direction
	//				Parameters:
	//					int ship, direction value 0 or 1.
	//			void printShip(ostream & sout = cout) const;
	//
	//
	//	History log:
	//		
	//		
	//------------------------------------------------------------------------
	class CDirection
	{
	public:
		CDirection(int ship = 0);
		operator Direction() const { return m_direction; }
		void printShip(ostream & sout = cout) const;
	private:
		Direction m_direction;
	};

	ostream & operator<<(ostream & sout, const CDirection & ship);
	istream & operator>>(istream & sin, CDirection & ship);
}

#endif