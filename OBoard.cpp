#include "stdafx.h"
#include "OBoard.h"
#include "OMove.h"

OthelloBoard::OthelloBoard()
{
	mBoard[BOARD_SIZE/2 - 1][BOARD_SIZE/2 - 1] = { WHITE };
	mBoard[BOARD_SIZE/2 - 1][BOARD_SIZE/2] = { BLACK };
	mBoard[BOARD_SIZE/2][BOARD_SIZE/2 - 1] = { BLACK };
	mBoard[BOARD_SIZE/2][BOARD_SIZE/2] = { WHITE };

	mValue = 0;
	mNextPlayer = BLACK;
}

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

void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {

	for (int x = 0; x < BOARD_SIZE; x++) {
		for (int y = 0; y < BOARD_SIZE; y++) {

			bool enemy = false;
			int rBack = x, cBack = y, countPcs = 0;
			if (mBoard[x][y] != EMPTY) { continue; }

			for (int i = -1; i <= 1; i++) {
				if (enemy) { break; }

				for (int j = -1; j <= 1; j++) {
					if (enemy) { break; }

					if (i == 0 && j == 0) { continue; } //10
					if (!InBounds(x + i, y + j) && mBoard[x + i][y + j]
						== mNextPlayer) {
						continue;
					}

					x = rBack;
					y = cBack;

					if (mBoard[x + i][y + j] != EMPTY) { //15
						while (mBoard[x + i][y + j] == -mNextPlayer
							&& InBounds(x + i, y + j)) {
							x = x + i;
							y = y + j;
							countPcs++; //20
						}

						if (mBoard[x + i][y + j] == mNextPlayer
							&& countPcs >= 1 && InBounds(x + i, y + j)) {

							list->push_back(new OthelloMove(rBack, cBack));
							enemy = true;
							// pick a new square to avoid multiple possMoves 
							countPcs--; //25
						}
						countPcs = 0;
					}
				}
			}
			x = rBack, y = cBack;
		}
	}
	if (list->empty()) {
		OthelloMove *noPossibleMoves = CreateMove();
		list->push_back(noPossibleMoves); //30
	}
}


void OthelloBoard::UndoLastMove() {

	int tempR = mHistory.back()->mRow;
	int tempC = mHistory.back()->mCol;

	if (mHistory.back()->isMovePass()) mPassCount = 0;
	else {

		mBoard[tempR][tempC] = EMPTY;
		mValue += mNextPlayer;

		for (OthelloMove::FlipSet &flipEm : mHistory.back()->mEnemiesFlipped) {
			int oR = tempR, oC = tempC, count = flipEm.switched;
			// for each flipset in move->mFlips


			// walk X times (X == flip.switched) in the direction
			while (count > 0) {

				tempR = tempR + flipEm.rowDelta;
				tempC = tempC + flipEm.colDelta;

				//    change board back to opposite color
				mBoard[tempR][tempC] = mNextPlayer;

				//		adjust value
				mValue += mNextPlayer * 2;
				count--;
			}
			//count = 0;
			tempR = oR;
			tempC = oC;
		}
	}
	delete mHistory.back();
	mHistory.pop_back();
	mNextPlayer = -mNextPlayer; //19
}
