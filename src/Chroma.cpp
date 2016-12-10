// FILE: Chroma.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements Chroma, a class used for representing tones without a specified octave

#include "Chroma.h"


const double Chroma::freqs[] = { 523.251, 554.365, 587.330, 622.254,
								659.485, 698.456, 739.989, 783.991,
								830.609, 880.000, 932.328, 987.767 };

Chroma::Chroma() {
	//stk::Stk::setRawwavePath("C:/Users/Adam/Desktop/of_v0.9.7_vs_release/apps/myApps/ofxMusicalBejeweled/bin/data/rawwaves");
	tone = -1;
	freq = 0.0;
	font.loadFont(CHROMA_FONT_NAME, CHROMA_FONT_SIZE);
	//instrument.setBodySize(0.3);
	//instrument.setPluckPosition(0.5);
}


Chroma::~Chroma() {}

std::string Chroma::getName() {
	return names[::key][tone];
}

int Chroma::getTone() {
	return tone;
}

float Chroma::getFreq() {
	return (float)freq;
}

void Chroma::setTone(int tone, bool low) {
	this->tone = tone;
	freq = (float)freqs[(tone + ::key) % 12];
	//freq = (float)freqs[tone];
	if (low) freq /= 2.0;
	instrument.setFrequency(freq);
}


void Chroma::tick(float* buffer, int bufferSize) {
	stk::StkFrames frames(bufferSize, 2);
	instrument.tick(frames, 0);
	for (int i = 0; i < bufferSize; i++) {
		buffer[2 * i] += frames(i, 0);
		buffer[2 * i + 1] += frames(i, 0);
	}
}

void Chroma::draw(int x, int y, int squareSide, int movingFrame, int maxDistance, int hue) {
	if (deleted) {
		return;
	}
	int cellX = x + squareSide * col;
	int cellY = y + squareSide * row;
	if (falling) {
		cellY += min(movingFrame * movingFrame * GRAVITY, maxDistance);
	}
	if (highlighted) ofSetColor(ofColor::fromHsb(hue, SATURATION, BRIGHTNESS));
	else ofSetColor(235, 235, 235);
	std::string name = names[::key][tone];
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

void Chroma::instrumentOn() {
	//instrument.noteOn(freq, 1.0);
}

void Chroma::instrumentOff() {
	//instrument.noteOff(1.0);
}