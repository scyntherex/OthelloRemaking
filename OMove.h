#ifndef __OTHELLOMOVE_H
#define __OTHELLOMOVE_H

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>

class OthelloMove {
public:
	/*
	This assignment operator takes a string representation of an Othellomove
	and uses it to initialize the move. The string is in the format
	(r, c); OR is the string "pass". [The user will not enter (-1,-1) to pass
	anymore.]
	*/
	OthelloMove& operator= (const std::string &);
	/*
	Compares two OthelloMove objects for equality (if rows and cols are same).
	*/
	friend bool operator== (const OthelloMove &lhs, const OthelloMove &rhs);
	/*
	Converts the OthelloMove into a string representation, one that could be
	used correctly with operator=(string). Returns "pass" if move is a pass.
	*/
	operator std::string() const;
	// Returns true if the move represents a Pass.
	// TO DO: fill in this method.
	inline bool isMovePass() {/* return true if this move is a "pass" */ 
		return(mRow == -1 && mCol == -1);
	}

	/*used to check on moves on heap. for debugging purposes.
	static int mOnHeap;

	static void* operator new(std::size_t sz) {
		mOnHeap++;
		//std::cout << "operator new: " << mOnHeap << " OthelloMoves on the heap" << std::endl;
		return ::operator new(sz);
	}

	static void operator delete(void* ptr, std::size_t sz) {
		mOnHeap--;
		//std::cout << "operator delete: " << mOnHeap << " OthelloMoves on the heap" << std::endl;
		::operator delete(ptr);
	}*/

private:
	// OthelloBoard is a friend so it can access mRow and mCol.
	friend class OthelloBoard;
	/*
	A FlipSet tracks a direction and # of pieces that got flipped when this
	move was applied. See spec.
	*/
	class FlipSet {
		public:
			FlipSet(char sw, char rDelta, char cDelta) : 
			switched(sw), rowDelta(rDelta), colDelta(cDelta){}

			char switched, rowDelta, colDelta;
	};
	// the row and column of the move
	int mRow, mCol;
	// a list of FlipSets representing the enemy pieces flipped by this move
	std::vector<FlipSet> mEnemiesFlipped;
	// Default constructor: initializes this move as a PASS.
	OthelloMove();
	/*
	2-parameter constructor: initializes this move with the given
	row and column.
	*/
	OthelloMove(int row, int col);
	/*
	Adds a FlipSet to the move's vector of sets. Used to keep track of how many
	enemy pieces were flipped in each direction when this move was applied.
	This function is private, but OthelloBoard has friend access.
	*/
	void AddToFlipSet(FlipSet set) { mEnemiesFlipped.push_back(set); }
};
#endif
