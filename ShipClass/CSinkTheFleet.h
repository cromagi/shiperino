//-----------------------------------------------------------------------------
// File: CSinkTheFleet.h
//
//-----------------------------------------------------------------------------
#ifndef CSINKTHEFLEET_H
#include <iostream>

#include "CPlayer.h"


namespace P4_CSinkFleet
{
	class CSinkTheFleet
	{
	public:
        // constructor
		CSinkTheFleet(char gridSize);
        // destructor
		~CSinkTheFleet(void);
        // accessors
		char getGridSize(void) { return m_gridSize;  }
        // mutators
		void setGridSize(char gridSize) { m_gridSize = gridSize; }
        // methods
		int play(void);
		CPlayer operator[](short index) { return m_players[index]; }
		static void header(void);
		static void endbox(short player);

        // other classes
		friend class CPlayer;

	private:
		CPlayer m_players[NUMPLAYERS];
		char m_gridSize;
		CPlayer player1;
		CPlayer player2;
	};


}
#endif