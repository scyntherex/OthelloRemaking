#ifndef __OTHELLOVIEW_H
#define __OTHELLOVIEW_H

#include "stdafx.h"
#include <iostream>
#include "OBoard.h"

/*
An MVC "View" class for printing the model of the othello board. Acts as a
"wrapper" around an OthelloBoard pointer and handles requests to print that
board to a stream by overloading operator<<. Friend of OthelloBoard.
*/
class OthelloView {
private:
	//This is the Othello actual board pointer.
	OthelloBoard *mOthelloBoard;

	//This prints the visuals.
	void PrintBoard(std::ostream &s) const;
public:
	OthelloView(OthelloBoard *b) : mOthelloBoard(b) {}

	// Overloaded operator<< so you can << an OthelloView object to cout.
	friend std::ostream& operator<<(std::ostream &, const OthelloView &);
};
#endif