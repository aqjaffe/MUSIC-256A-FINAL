// FILE: Grid.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Grid class

#ifndef GRID_H
#define GRID_H


#include "ofMain.h"
#include "Constants.h"
#include "PlayableChord.h"
#include "Chroma.h"
#include <algorithm>
#include <random>
#include <vector>
#include <chrono>

class Grid
{
public:
	Grid();
	~Grid();
	Chroma getChroma(int row, int col);
	void update();
	void draw(int x, int y, int side, int hue);
	void highlightBlocks(int startRow, int startCol, int endRow, int endCol);
	void highlightClear();
	void highlightErase();
	PlayableChord* getHighlighted();
	void reset();
	bool isMoving();

private:
	// for randomizing the note distribution
	unsigned seed;
	default_random_engine generator;
	const discrete_distribution<int>* distribution;
	const discrete_distribution<int>* uniform;

	// some machinery
	Chroma notes[GRID_NBLOCKS][GRID_NBLOCKS];
	int deletedChroma[MAX_NCHROMA][2];
	int nDeletedChroma;

	// some graphical elements
	int chromaSize;
	int movingFrame;
	int distanceToFall;
	
	// some private member functions
	bool isHighlightedVertical();
	bool isFalling(int row, int col);
	bool isDeleted(int row, int col);
	void transferFalling();
	void setFalling();
};

#endif