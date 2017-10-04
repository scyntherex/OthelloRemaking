#include "stdafx.h"
#include <iostream>
#include <sstream>
#include "OMove.h"
#include "OExceptions.h"
#include "OBoard.h"

using namespace std;

OthelloMove::OthelloMove() {
	mRow = -1;
	mCol = -1;
}

OthelloMove::OthelloMove(int row, int col) :
	mRow(row), mCol(col) {
}

OthelloMove& OthelloMove::operator= (const std::string &rhs) {
	if (rhs == "pass") {
		mRow = -1;
		mCol = -1;
	}
	else {
		istringstream cin(rhs);
		char decoy;
		cin >> decoy >> mRow >> decoy >> mCol >> decoy;
		if (!OthelloBoard::InBounds(mRow, mCol))
			throw OthelloException("Move not In Bounds!");
	}
	return *this;
}

bool operator== (const OthelloMove &lhs, const OthelloMove &rhs) {
	return(lhs.mRow == rhs.mRow && lhs.mCol == rhs.mCol);
}

OthelloMove::operator string() const {
	if (isMovePass)
		return "PASS^";
	else
		return "(" + to_string(mRow) + "," + to_string(mCol) + ")";
}