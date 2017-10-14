// OthelloRemake.cpp : Main class.
//

#include "OBoard.h"
#include "OMove.h"
#include "OView.h"
#include "OExceptions.h"
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
	OthelloBoard board; // the state of the game board
	OthelloView v(&board); // a View for outputting the board via operator<<
	string userInput; // a string to hold the user's command choice

	cout << "Hello Othello Time!" << endl;
	do {
		cout << v << endl;
		cout << "Enter a command:" << endl;
		cout << "move (x,x): makes 1 move of the game." << endl;
		cout << "quit: ends the game with current score." << endl;
		getline(cin, userInput);

		// move (r,c)
		if (userInput.substr(0, 4) == "move") {
			string moveStr = userInput.substr(5);
			//bool goodMove = false;
			bool goodMove = true;
			OthelloMove *m = board.CreateMove(); //20

			try {
				*m = moveStr;
				//for (auto itr = possMoves.begin(); itr < possMoves.end(); itr++) {
					//OthelloMove *valid = *itr;
					//if (*valid == *m) {
						//goodMove = true;
					//}
				//}
				if (goodMove) {
					cout << "Applying the move " << (string)(*m) << endl;
					board.ApplyMove(m);
				}
				else { //30
					cout << "\nNAHHH Invalid Move!" << endl;
					delete m;
				}
			}
			catch (OthelloException &s) {
				cout << "\n" << s.what() << endl;
				delete m;
			}
		}

		else if (userInput == "quit") {
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

