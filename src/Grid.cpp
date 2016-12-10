// FILE: Grid.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements Grid, a class which contains a square grid of chroma

#include "Grid.h"


Grid::Grid() {
	seed = chrono::system_clock::now().time_since_epoch().count();
	generator.seed(seed);
	uniform = new std::discrete_distribution<int> { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0 };
	distribution = new std::discrete_distribution<int>{ 1.97, 0.02, 1.07, 0.00, 1.51, 1.01, 0.06, 1.58, 0.10, 1.63, 0.02, 1.00 };
	for (int i = 0; i < GRID_NBLOCKS; i++) {
		for (int j = 0; j < GRID_NBLOCKS; j++) {
			float r = rand() / (float)RAND_MAX;
			float b = 1.0 - 1.0 / pow((float)::level, 0.3);
			if (r >= b)
				notes[i][j].setTone((*distribution)(generator), false);
			else
				notes[i][j].setTone((*uniform)(generator), false);
			notes[i][j].setIndex(i, j);
			notes[i][j].setHighlight(false);
			notes[i][j].setDeleted(false);
		}
	}
	chromaSize = GRID_SIZE / GRID_NBLOCKS;
	movingFrame = -1;
	nDeletedChroma = 0;
}


Grid::~Grid() {
	delete uniform;
	delete distribution;
}


Chroma Grid::getChroma(int row, int col) {
	return notes[row][col];
}


void Grid::update() {
	if (movingFrame * movingFrame * GRAVITY >= distanceToFall) {
		movingFrame = -1;
		transferFalling();
		nDeletedChroma = 0;
	} else if (movingFrame > -1) {
		movingFrame++;
	}
	setFalling();
}


void Grid::draw(int x, int y, int side, int hue) {
	ofPushStyle();
	for (int i = GRID_NBLOCKS - 1; i >= 0; i--) {
		for (int j = GRID_NBLOCKS - 1; j >= 0; j--) {
			notes[i][j].draw(x, y, chromaSize, movingFrame, distanceToFall, hue);
		}
	}
	ofPopStyle();
}


void Grid::highlightBlocks(int startRow, int startCol, int endRow, int endCol) {
	nDeletedChroma = 0;
	if (startRow == endRow) {
		highlightClear();
		if (startCol < endCol) {
			int stop = min(endCol, startCol + MAX_NCHROMA - 1);
			for (int j = startCol; j <= stop; j++) {
				notes[startRow][j].setHighlight(true);
			}
		}
		else if (startCol > endCol) {
			int start = max(endCol, startCol - MAX_NCHROMA + 1);
			for (int j = start; j <= startCol; j++) {
				notes[startRow][j].setHighlight(true);
			}
		}
	} else if (startCol == endCol) {
		highlightClear();
		if (startRow < endRow) {
			int stop = min(endRow, startRow + MAX_NCHROMA - 1);
			for (int i = startRow; i <= stop; i++) {
				notes[i][startCol].setHighlight(true);
			}
		}
		else if (startRow > endRow) {
			int start = max(endRow, startRow - MAX_NCHROMA + 1);
			for (int i = start; i <= startRow; i++) {
				notes[i][startCol].setHighlight(true);
			}
		}
	}
}


void Grid::highlightClear() {
	for (int i = 0; i < GRID_NBLOCKS; i++) {
		for (int j = 0; j < GRID_NBLOCKS; j++) {
			notes[i][j].setDeleted(false);
			notes[i][j].setHighlight(false);
		}
	}
}

void Grid::highlightErase() {
	nDeletedChroma = 0;
	for (int i = GRID_NBLOCKS - 1; i >= 0; i--) {
		for (int j = GRID_NBLOCKS - 1; j >= 0; j--) {
			if (notes[i][j].isHighlighted()) {
				notes[i][j].setHighlight(false);
				notes[i][j].setDeleted(true);
				deletedChroma[nDeletedChroma][0] = i; // 0 for row
				deletedChroma[nDeletedChroma][1] = j; // 1 for col
				nDeletedChroma++;
			}
		}
	}
	movingFrame = 0;
	if (isHighlightedVertical()) {
		distanceToFall = chromaSize * (deletedChroma[0][0] - deletedChroma[nDeletedChroma - 1][0] + 1);
	} else {
		distanceToFall = chromaSize;
	}
}

PlayableChord* Grid::getHighlighted() {
	PlayableChord* chord = new PlayableChord();
	for (int i = 0; i < GRID_NBLOCKS; i++) {
		for (int j = 0; j < GRID_NBLOCKS; j++) {
			if (notes[i][j].isHighlighted()) chord->addChroma(notes[i][j]);
		}
	}
	return chord;
}

bool Grid::isMoving() {
	return movingFrame > -1;
}


bool Grid::isHighlightedVertical() {
	return deletedChroma[0][1] == deletedChroma[1][1];
}


bool Grid::isFalling(int row, int col) {
	if (nDeletedChroma < 3) return false;
	int bottomRow = deletedChroma[nDeletedChroma - 1][0];
	int leftCol = deletedChroma[nDeletedChroma - 1][1];
	int rightCol = deletedChroma[0][1];
	return leftCol <= col && col <= rightCol && row < bottomRow;
}

bool Grid::isDeleted(int row, int col) {
	for (int i = 0; i < nDeletedChroma; i++) {
		if (deletedChroma[i][0] == row && deletedChroma[i][1] == col) return true;
	}
	return false;
}

void Grid::transferFalling() {
	for (int i = GRID_NBLOCKS - 1; i >= 0; i--) {
		for (int j = GRID_NBLOCKS - 1; j >= 0; j--) {
			int vert = deletedChroma[0][0] - deletedChroma[nDeletedChroma - 1][0] + 1;
			if (notes[i][j].isFalling() || notes[i][j].isDeleted()) {
				if (i >= vert) notes[i][j] = notes[i - vert][j];
				else notes[i][j].setTone((*distribution)(generator), false);
				notes[i][j].setIndex(i, j);
				notes[i][j].setFalling(false);
				notes[i][j].setDeleted(false);
			}
		}
	}
}

void Grid::setFalling() {
	for (int i = GRID_NBLOCKS - 1; i >= 0; i--) {
		for (int j = GRID_NBLOCKS - 1; j >= 0; j--) {
			if (isFalling(i, j)) notes[i][j].setFalling(true);
		}
	}
}

void Grid::reset() {
	for (int i = 0; i < GRID_NBLOCKS; i++) {
		for (int j = 0; j < GRID_NBLOCKS; j++) {
			float r = rand() / (float)RAND_MAX;
			float b = 1.0 - 1.0 / pow((float)::level, 0.3);
			if (r >= b)
				notes[i][j].setTone((*distribution)(generator), false);
			else
				notes[i][j].setTone((*uniform)(generator), false);
			notes[i][j].setIndex(i, j);
			notes[i][j].setHighlight(false);
			notes[i][j].setDeleted(false);
		}
	}
}