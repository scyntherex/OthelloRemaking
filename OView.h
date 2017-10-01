#include "stdafx.h"
#include "OBoard.h"

/*
An MVC "View" class for printing the model of the othello board. Acts as a
"wrapper" around an OthelloBoard pointer and handles requests to print that
board to a stream by overloading operator<<. Friend of OthelloBoard.
*/
class OthelloView {
public:
	OthelloView(OthelloBoard *b) : mOthelloBoard(b) {}

	// Overloaded operator<< so you can << an OthelloView object to cout.
	friend std::ostream& operator<<(std::ostream &, const OthelloView &);
private:
	//This is the Othello actual board pointer.
	OthelloBoard *mOthelloBoard;

	//This prints the visuals.
	void PrintBoard(std::ostream &s) const;
};