// OthelloRemake.cpp : Main class.
//

#include "stdafx.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "OBoard.h"
#include "OView.h"


using namespace std;

int main()
{
	OthelloBoard board; // the state of the game board
	OthelloView v(&board); // a View for outputting the board via operator<<

	cout << "Hello Othello Time!" << endl;

	cout << v << endl;
	
    return 0;
}

