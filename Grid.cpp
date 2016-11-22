// FILE: Grid.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements Grid, a class which contains a square grid of chroma

#include "Grid.h"


Grid::Grid() {
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	const std::discrete_distribution<int> distribution { 1.97, 0.02, 1.07, 0.00, 1.51, 1.01, 0.06, 1.58, 1.10, 1.63, 0.02, 1.00 };
	chromaFont.loadFont("Arial", 14);
	for (int i = 0; i < GRID_NBLOCKS; i++) {
		for (int j = 0; j < GRID_NBLOCKS; j++) {
			notes[i][j].setTone(distribution(generator));
			highlight[i][j] = false;
		}
	}
}


Grid::~Grid() {}


Chroma Grid::getChroma(int row, int col) {
	return notes[row][col];
}


void Grid::draw(int x, int y, int side) {
	ofPushStyle();
	for (int i = 0; i < GRID_NBLOCKS; i++) {
		for (int j = 0; j < GRID_NBLOCKS; j++) {
			ofFill();
			if (highlight[i][j]) ofSetColor(GRID_HIGHLIGHT_COLOR);
			else ofSetColor(GRID_TILE_COLOR);
			int squareSide = side / (float)GRID_NBLOCKS;
			ofRectangle square(x + squareSide * i, y + squareSide * j, squareSide, squareSide);
			ofDrawRectangle(square);

			ofNoFill();
			ofSetColor(GRID_BORDER_COLOR);
			ofDrawRectangle(square);

			ofSetColor(GRID_FONT_COLOR);
			std::string name = notes[i][j].getName();
			chromaFont.drawString(name, x + squareSide * (i + 0.5) - 0.5 * chromaFont.stringWidth(name), 
				y + squareSide * (j + 0.5) + 0.5 * chromaFont.stringHeight(name));
		}
	}
	ofPopStyle();
}


void Grid::highlightBlocks(int startRow, int startCol, int endRow, int endCol) {
	if (startRow == endRow) {
		highlightClear();
		if (startCol < endCol) {
			for (int i = startCol; i <= endCol; i++) {
				highlight[startRow][i] = true;
			}
		}
		else if (startCol > endCol) {
			for (int i = endCol; i <= startCol; i++) {
				highlight[startRow][i] = true;
			}
		}
		else {
			highlight[startRow][startCol] = true;
		}
	} else if (startCol == endCol) {
		highlightClear();
		if (startRow < endRow) {
			for (int i = startRow; i <= endRow; i++) {
				highlight[i][startCol] = true;
			}
		}
		else if (startRow > endRow) {
			for (int i = endRow; i <= startRow; i++) {
				highlight[i][startCol] = true;
			}
		}
		else {
			highlight[startRow][startCol] = true;
		}
	}
}


void Grid::highlightClear() {
	for (int i = 0; i < GRID_NBLOCKS; i++) {
		for (int j = 0; j < GRID_NBLOCKS; j++) {
			highlight[i][j] = false;
		}
	}
}

PlayableChord* Grid::getHighlighted() {
	PlayableChord* chord = new PlayableChord();
	for (int i = 0; i < GRID_NBLOCKS; i++) {
		for (int j = 0; j < GRID_NBLOCKS; j++) {
			if (highlight[i][j]) chord->addChroma(notes[i][j]);
		}
	}
	return chord;
}

