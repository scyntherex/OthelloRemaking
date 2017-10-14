#include "stdafx.h"
#include "OBoard.h"

OthelloBoard::OthelloBoard()
{
	mBoard[BOARD_SIZE/2 - 1][BOARD_SIZE/2 - 1] = { WHITE };
	mBoard[BOARD_SIZE/2 - 1][BOARD_SIZE/2] = { BLACK };
	mBoard[BOARD_SIZE/2][BOARD_SIZE/2 - 1] = { BLACK };
	mBoard[BOARD_SIZE/2][BOARD_SIZE/2] = { WHITE };

	mValue = 0;
	mNextPlayer = BLACK;
}

/*void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {
	;
}*/

void OthelloBoard::ApplyMove(OthelloMove *move) {
	int countPcs = 0, rBack = move->mRow, cBack = move->mCol;
	int r = rBack, c = cBack;
	
	if (move->isMovePass()) { mPassCount++; } 

	else {
		//Place move
		mBoard[r][c] = mNextPlayer;
		//Change the score of the game with tthat one piece
		mValue += mNextPlayer;
		//Now look on all 8 directions
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				//No to self
				if (i == 0 && j == 0) { continue; } 
				//Check borders
				if (InBounds(r, c)) { r = rBack, c = cBack; }
				//Checking the direction to flip
				if (mBoard[r + i][c + j] != EMPTY) {
					while (mBoard[r + i][c + j] == -mNextPlayer) {
						r = r + i;
						c = c + j;
						countPcs++;
					}
					//Stop if a piece of the user is found
					if (mBoard[r + i][c + j] == mNextPlayer
						&& countPcs >= 1 && InBounds(r + i, c + j)) {
						//For history of moves
						move->AddToFlipSet(OthelloMove::FlipSet(countPcs, i, j));

						while (mBoard[r + i][c + j] == mNextPlayer
							&& countPcs >= 1 && InBounds(r + i, c + j)) {
							r = r - i;
							c = c - j;

							mBoard[r + i][c + j] = mNextPlayer;
							mValue += mNextPlayer * 2;
							countPcs--;
						}

					}
					countPcs = 0; // for resetting with mValue 
				}
				r = rBack, c = cBack;
			}
		}
		mPassCount = 0;
	}
	mHistory.push_back(move);
	mNextPlayer = -mNextPlayer; //30
}

/*
void OthelloBoard::UndoLastMove() {
	;
}
*/
