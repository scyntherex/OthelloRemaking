#include "stdafx.h"
#include "OBoard.h"

OthelloBoard::OthelloBoard()
{
	mBoard[BOARD_SIZE - 1][BOARD_SIZE - 1] = { WHITE };
	mBoard[BOARD_SIZE - 1][BOARD_SIZE] = { BLACK };
	mBoard[BOARD_SIZE][BOARD_SIZE - 1] = { BLACK };
	mBoard[BOARD_SIZE][BOARD_SIZE] = { WHITE };

	mValue = 0;
	mNextPlayer = BLACK;
}

void OthelloBoard::GetPossibleMoves(std::vector<OthelloMove *> *list) const {
	;
}

void OthelloBoard::ApplyMove(OthelloMove *move) {
	;
}

void OthelloBoard::UndoLastMove() {
	;
}

