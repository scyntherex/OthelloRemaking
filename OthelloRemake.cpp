// OthelloRemake.cpp : Main class.
//
#include "stdafx.h"
#include "OBoard.h"
#include "OMove.h"
#include "OView.h"
#include "OExceptions.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

int main() {
	// Initialization
	OthelloBoard board; // the state of the game board
	OthelloView v(&board); // a View for outputting the board via operator<<
	string userInput; // a string to hold the user's command choice
	vector<OthelloMove *> possMoves; // a holder for possible moves

	// Main loop
	cout << "\nOthello!" << endl;

	do {
		// Print the game board using the OthelloView object
		cout << v << endl;
		if (board.GetNextPlayer() == 1) {
			cout << "\nBlack Player's Turn " << endl;
		}
		else cout << "\nWhite Player's Turn " << endl; //10

		// Print all possible moves
		// Createth
		board.GetPossibleMoves(&possMoves);
		cout << "\nPossible moves: " << endl;
		for (OthelloMove *GetPossibleMoves : possMoves) {
			cout << (string)*GetPossibleMoves << ", ";
		}

		// Ask to input a command
		cout << "\nEnter a command: " << endl;

		// Command loop:
		getline(cin, userInput);


		// move (r,c)
		if (userInput.substr(0, 4) == "move") {
			string moveStr = userInput.substr(5);
			bool goodMove = false;
			OthelloMove *m = board.CreateMove(); //20

			try {
				*m = moveStr;
				for (auto itr = possMoves.begin(); itr < possMoves.end(); itr++) {
					OthelloMove *valid = *itr;
					if (*valid == *m) {
						goodMove = true;
					}
				}
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

		// undo n
		else if (userInput.substr(0, 4) == "undo") {

			int s = stoi(userInput.substr(4));
			if (s > board.GetMoveCount())
				s = board.GetMoveCount();

			for (int i = 0; i < s; i++) {
				board.UndoLastMove();
			}
		}

		// showValue
		else if (userInput == "showValue") {
			cout << "Points: " << board.GetValue() << endl;
		}

		// showHistory
		else if (userInput == "showHistory") {

			int other = board.GetNextPlayer();
			cout << "\nThere were " << board.GetMoveCount() << " move(s).";
			cout << "\nPrevious Moves: " << endl;

			auto hist = board.GetAllRecentMoves();
			for (auto itr = hist->rbegin(); itr != hist->rend(); itr++) { //50
				if (other == -1) { cout << "BLACK "; }
				else { cout << "WHITE "; }
				cout << (string)**itr << endl;
				other *= -1;
			}
		}

		// quit
		else if (userInput == "quit") {
			OthelloMove *m = board.CreateMove();
			*m = "pass";
			board.ApplyMove(m);
			OthelloMove *n = board.CreateMove();
			*n = "pass"; //60
			board.ApplyMove(n);
			delete m;
			delete n;
		}
		else;

		//Destroyeth
		for (OthelloMove *om : possMoves) {
			delete om;
		}
		possMoves.clear();

	} while (!board.IsFinished());

	cout << "\nGAME OVER!!!" << endl;
	if (board.GetValue() > 0) { //70
		cout << "BLACK WINS!" << endl;
	}
	else if (board.GetValue() < 0) {
		cout << "WHITE WINS." << endl;
	}
	else
		cout << "Tie. Your're both LOSERS..." << endl;
	return 0;
}

