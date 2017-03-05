//-----------------------------------------------------------------------------
// File: CSinkTheFleet.cpp
//
//-----------------------------------------------------------------------------

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include "CSinkTheFleet.h"

using namespace std;

namespace P4_CSinkFleet
{
	CSinkTheFleet::CSinkTheFleet(char gridSize)
	{
		m_gridSize = gridSize;
//		player1 = { 0, gridSize };
//		player2 = { 1, gridSize };
		player1 = CPlayer( 0, gridSize );
		player2 = CPlayer( 1, gridSize );

//		m_players[0] = player1;
//		m_players[1] = player2;
		m_players[0] = player1;
		m_players[1] = player2;
	}

	CSinkTheFleet::~CSinkTheFleet(void) {}


	void CSinkTheFleet::header(void)
	{
		const string empty;
		const string sink("SINK THE FLEET!");
		const string better("Now with OOP!");
		const string name1("Thurman Gillespy, Jason Duncan, Jason Guatama");
		const string name2("David Landry and Matt Schroeder");
		const string by("Edmonds Community College CS 132");
		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, sink, BOXWIDTH, 'C');
		boxLine(cout, better, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, by, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, name1, BOXWIDTH, 'C');
		boxLine(cout, name2, BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}

	void CSinkTheFleet::endbox(short player)
	{
		const string empty;
		ostringstream msg;
		msg << "Congratulations player " << player + 1 << "!";
		boxTop(cout, BOXWIDTH);
		boxLine(cout, empty, BOXWIDTH);
		boxLine(cout, msg.str(), BOXWIDTH, 'C');
		boxLine(cout, empty, BOXWIDTH);
		boxBottom(cout, BOXWIDTH);
	}

	int CSinkTheFleet::play(void)
	{
		short winner = 0;
		char choice = 0;
		string filename;
		short whichPlayer = -1;
		bool reshoot = false;
		bool gameOver = false;
		bool fileLoaded = false;
		char gridSize = m_gridSize;
		Ship shotStatus = NOSHIP;
		CPlayer *curPlayer = nullptr;
		CPlayer *curTarget = nullptr;

		// start play - ask each player how to set up game
		for (whichPlayer = 0; whichPlayer < NUMPLAYERS; whichPlayer++)
		{
			curPlayer = &m_players[whichPlayer];
			do {
				cout << "Player " << whichPlayer + 1 << ". ";
				choice = safeChoice(
					"Would you like to read starting grid from a file?", 'Y', 'N');
				if (choice == 'Y')
				{
					cout << "Enter file name: ";
					cin >> filename;
					// load the file. If failure, repeat the loop
					if (curPlayer->getGrid(filename + ".shp") == false)
					{
						choice = 'N';
						continue;
					}
				}
				else
				{
					// let the user enter the coordinates
					curPlayer->setShips(); // ADD PARAMETERS ONCE DEFINED
				}
				// print grid, ask user if ok
				curPlayer->printGrid(cout, 0); // FIX THIS -- ONLY 1 PARAM NEEDED
				choice = safeChoice("OK?", 'Y', 'N');
				if (choice == 'N')
				{
					// need to clear gameGrid[0] 
					// before reentering ship coordinates
					curPlayer->clearGrid(); // ADD METHOD AND PARAMETERS
				}
				cin.ignore(BUFFER_SIZE, '\n');
				system("cls");
			} while (choice == 'N');
		} // end for

		system("cls");
		header();
		cout << "Press <enter> to continue the battle!" << endl;
		cin.ignore(BUFFER_SIZE, '\n');

		// games are set - time to shart shooting
		while (!gameOver)
		{
			// give each player a turn
			for (whichPlayer = 0; whichPlayer < NUMPLAYERS && gameOver == false; whichPlayer++)
			{
				curPlayer = &m_players[whichPlayer];
				curTarget = &m_players[whichPlayer == 0 ? 1: 0]; // the other guy
				// but keep giving the same player a turn if gets a HIT
				do // while reShoot == true
				{
					curPlayer->printGrid(cout, 1); 

					if (reshoot == true)
						cout << "Player " << whichPlayer + 1 <<
						" shoots again! Enter coordinates for firing:" << endl;
					else
						cout << "Player " << whichPlayer + 1 <<
						". Enter coordinates for firing:" << endl;

					// get shot coordinates, and check for a HIT
					CCell cell;
					cell.inputCoordinates(cin, gridSize);
					// check if user already fired a shot at these coord
					//					shotStatus =
					//						game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col];
					shotStatus = curPlayer->getHitStatus(cell);
					if (shotStatus == HIT || shotStatus == MISSED)
					{
						cout << "You have already fired a shot "
							"at those coordinates.";
						cout << endl << "Press <enter>";
						reshoot = true;
						cin.ignore(BUFFER_SIZE, '\n');
						continue;
					}
					// which ship was hit?
					//					shipHit = game[whichPlayer == 0 ? 1 :
					//						0].m_gameGrid[0][coord.m_row][coord.m_col];
					CShip shipHit = curTarget->getShipStatus(cell); // ?? curPlayer
					// now mark the grid
					if (shipHit == NOSHIP)
					{
						// record a MISSED
						//						game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col]
						//							= MISSED;
						curPlayer->setHitStatus(cell, MISSED);
						curPlayer->printGrid(cout, 1);
						reshoot = false;
						cout << "MISSED!" << endl << "Press <enter>";
						cin.ignore(BUFFER_SIZE, '\n');
					}
					else
					{
						// record a HIT
						//						game[whichPlayer].m_gameGrid[1][coord.m_row][coord.m_col]
						//							= HIT;
						curPlayer->setHitStatus(cell, HIT);
						curTarget->hitShip(shipHit); 

						// decrement total number of pieces
						// game[whichPlayer == 0 ? 1 : 0].m_piecesLeft--;
						// what ship type is at that location?
						// whichShip = game[whichPlayer == 0 ? 1 : 0].m_gameGrid[0][coord.m_row][coord.m_col];
						// decrement pieces of that ship
						//	game[whichPlayer == 0 ? 1 : 0].m_ships[whichShip].m_piecesLeft--;

						curPlayer->printGrid(cout, 1);
						reshoot = true;
						cout << "HIT!" << endl;

						// check to see if that ship has been sunk
//						if (game[whichPlayer == 0 ? 1 :
//							0].m_ships[shipHit].m_piecesLeft <= 0)
						if ( curTarget->isSunk(shipHit) ) // FAILURE HERE
						{
							//cout << "You sank the " << curTarget->getShipName(shipHit)
							CShip hitShip;
							cout << "You sank the ";
							shipHit.printName();  //curTarget[cell.getRow()][cell.getCol()].getName() //printName()	
							cout << "!" << endl;
						}
						cout << "Press <enter>";
						cin.ignore(BUFFER_SIZE, '\n');
					} // end if

					// if total pieces left == 0
					// declare the winner and set flags
					if (curTarget->getPiecesLeft() <= 0)
					{
						gameOver = true;
						reshoot = false;
//						cout << "Congratulations Player " << whichPlayer + 1 <<
//							", you have won the game!" << endl;
					}
				} while (reshoot == true);
			} // end for whichPlayer
		} // end while !gameOver

		return winner;

	} // CSinkFleet::play

} // namespace


