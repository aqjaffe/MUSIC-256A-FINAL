// FILE: Grid.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Grid class

#ifndef GRID_H
#define GRID_H


#include "ofMain.h"
#include "Chroma.h"
#include "PlayableChord.h"
#include "Constants.h"
#include <random>
#include <chrono>

class Grid
{
public:
	Grid();
	~Grid();
	Chroma getChroma(int row, int col);
	void draw(int x, int y, int side);
	void highlightBlocks(int startRow, int startCol, int endRow, int endCol);
	void highlightClear();
	PlayableChord* getHighlighted();

private:
	ofTrueTypeFont chromaFont;
	Chroma notes[GRID_NBLOCKS][GRID_NBLOCKS];
	bool highlight[GRID_NBLOCKS][GRID_NBLOCKS];
};

#endif