// FILE: Grid.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Grid class

#pragma once

#include <random>
#include <chrono>
#include "ofMain.h"
#include "Chroma.h"
#include "Constants.h"


class Grid
{
public:
	Grid();
	~Grid();
	Chroma getChroma(int row, int col);
	void draw(int x, int y, int side);
	void highlightBlocks(int startRow, int startCol, int endRow, int endCol);
	void highlightClear();
	std::string getHighlighted();

private:
	ofTrueTypeFont chromaFont;
	Chroma notes[GRID_NBLOCKS][GRID_NBLOCKS];
	bool highlight[GRID_NBLOCKS][GRID_NBLOCKS];
};

