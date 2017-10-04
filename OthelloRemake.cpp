// OthelloRemake.cpp : Main class.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "OBoard.h"
#include "OView.h"


using namespace std;

int main()
{
	OthelloBoard board; // the state of the game board
	OthelloView v(&board); // a View for outputting the board via operator<<
	string userInput; // a string to hold the user's command choice

	cout << "Hello Othello Time!" << endl;
	do {
		cout << v << endl;
		cout << "Enter a command:" << endl;
		cout << "move (x,x): makes 1 move of the game." << endl;
		cout << "undo n: undoes n amount of moves from game." << endl;
		cout << "sv: shows the current score of the game." << endl;
		cout << "sh: shows the previous moves used in the game." << endl;
		cout << "quit: ends the game with current score." << endl;
		getline(cin, userInput);

		if (userInput == "quit") {
			OthelloMove *passCurrPlayer = board.CreateMove();
			*passCurrPlayer = "pass";
			board.ApplyMove(passCurrPlayer);
			OthelloMove *passNextPlayer = board.CreateMove();
			*passNextPlayer = "pass";
			board.ApplyMove(passNextPlayer);
			delete passCurrPlayer;
			delete passNextPlayer;
		}

		else;

	} while (!board.IsFinished());
	
	cout << "\nGAME OVER!!!" << endl;
    return 0;
}

