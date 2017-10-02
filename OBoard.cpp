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
}

void OthelloBoard::ApplyMove(OthelloMove *move) {
	;
}

void OthelloBoard::UndoLastMove() {
	;
}
*/
