// FILE: Grid.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Grid class

#ifndef GRID_H
#define GRID_H


#include "ofMain.h"
#include "Chroma.h"
#include "PlayableChord.h"
#include "Constants.h"
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
	void draw(int x, int y, int side);
	void highlightBlocks(int startRow, int startCol, int endRow, int endCol);
	void highlightClear();
	void highlightErase();
	PlayableChord* getHighlighted();
	bool isMoving();

private:
	unsigned seed;
	std::default_random_engine generator;
	const std::discrete_distribution<int>* distribution;
	Chroma notes[GRID_NBLOCKS][GRID_NBLOCKS];
	int chromaSize;
	int deletedChroma[MAX_NCHROMA][2];
	int nDeletedChroma;
	int movingFrame;
	int distanceToFall;

	bool isHighlightedVertical();
	bool isFalling(int row, int col);
	bool isDeleted(int row, int col);
	void transferFalling();
	void setFalling();
};

#endif