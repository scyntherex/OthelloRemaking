#include "stdafx.h"
#include <iostream>
#include "OView.h"

using namespace std;

void OthelloView::PrintBoard(ostream &s) const {
	s << "\n- 0 1 2 3 4 5 6 7" << endl;
	for (int i = 0; i <= 7; i++) {
		s << i;

		for (int j = 0; j <= 7; j++) {
			s << (mOthelloBoard->mBoard[i][j] == mOthelloBoard->EMPTY ? ' .' :
				mOthelloBoard->mBoard[i][j] == mOthelloBoard->BLACK ? ' B': ' W');
		}
		s << endl;
	}
}

ostream& operator<< (ostream &lhs, const OthelloView &rhs) {
	rhs.PrintBoard(lhs);
	return lhs;
}

