//-----------------------------------------------------------------------------
// File: CSinkFleetMain.cpp
//
//-----------------------------------------------------------------------------
#include <iostream>
#include <cstddef>
#include "safeio.h"
#include "CSinkTheFleet.h"

const int NO_WINNER = -1;

using namespace std;

int main(void)
{
	using namespace P4_CSinkFleet;

	char gridSize = 'S';
	char again = 'N';

	gridSize = safeChoice("Which size grid to you want to use?", 'S', 'L');

	do
	{
		short winner = NO_WINNER;
		while (winner == NO_WINNER)
		{
			CSinkTheFleet game(gridSize);
         // show header
			game.header();
			// play game until a winner
			winner = game.play();
			// announce winner
			game.endbox(winner);
		}
      // game falls out of scope, calling destructor
		// need to call cls?
		again = safeChoice("Play again?", 'Y', 'N');

	} while (again == 'Y');
    
    return EXIT_SUCCESS;
}