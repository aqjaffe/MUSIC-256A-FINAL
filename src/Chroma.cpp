// FILE: Chroma.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements Chroma, a class used for representing tones without a specified octave

#include "Chroma.h"

// identifies integer and string representations of the same chroma
const std::string Chroma::names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};
const double Chroma::freqs[] = { 523.251, 554.365, 587.330, 622.254,
								659.485, 698.456, 739.989, 783.991,
								830.609, 880.000, 932.328, 987.767 };

Chroma::Chroma() {
	tone = -1;
	name = "";
	freq = 0.0;
	currentAngle = 0.0;
	angleDelta = 0.0;
	font.loadFont(GRID_FONT_NAME, GRID_FONT_SIZE);
}


Chroma::~Chroma() {}

std::string Chroma::getName() {
	return name;
}

int Chroma::getTone() {
	return tone;
}

float Chroma::getFreq() {
	return (float)freq;
}

void Chroma::setTone(int tone, bool low) {
	this->tone = tone;
	name = names[tone];
	freq = (float)freqs[tone];
	if (low) freq /= 2.0;
	angleDelta = (float)(freq * 2.0 * M_PI / (float)SAMPLE_RATE);
}

float Chroma::tick() {
	if (tone == -1) {
		return 0.0;
	} else {
		float currentSample = std::sin(currentAngle);
		currentAngle += angleDelta;
		return currentSample;
	}
}

void Chroma::draw(int x, int y, int squareSide, int movingFrame, int maxDistance) {
	if (deleted) {
		return;
	}
	int cellX = x + squareSide * col;
	int cellY = y + squareSide * row;
	if (falling) {
		cellY += min(movingFrame * movingFrame * GRAVITY, maxDistance);
	}

	// draw the square tile
	ofRectangle square(cellX, cellY, squareSide, squareSide);
	if (highlighted) ofSetColor(GRID_HIGHLIGHT_COLOR);
	else ofSetColor(GRID_TILE_COLOR);
	ofFill();
	ofDrawRectangle(square);
	ofNoFill();
	ofSetColor(GRID_BORDER_COLOR);
	ofDrawRectangle(square);

	// draw the chroma name
	ofSetColor(GRID_FONT_COLOR);
	font.drawString(name, cellX + 0.5 * (squareSide - font.stringWidth(name)),
		cellY + 0.5 * (squareSide + font.stringHeight(name)));
}

void Chroma::setIndex(int row, int col) {
	this->row = row;
	this->col = col;
}

void Chroma::setHighlight(bool highlight) {
	this->highlighted = highlight;
}

bool Chroma::isHighlighted() {
	return highlighted;
}

void Chroma::setDeleted(bool deleted) {
	this->deleted = deleted;
}

bool Chroma::isDeleted() {
	return deleted;
}

void Chroma::setFalling(bool falling) {
	this->falling = falling;
}

bool Chroma::isFalling() {
	return falling;
}