// FILE: Chroma.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Chroma class

#ifndef CHROMA_H
#define CHROMA_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include <algorithm>
#include "Constants.h"
#include "ofMain.h"
#include "ofxStk.h"

class Chroma
{
public:
	Chroma();
	~Chroma();
	string getName();
	int getTone();
	float getFreq();
	void setTone(int tone, bool low);
	void tick(float* buffer, int bufferSize);
	void draw(int x, int y, int squareSide, int movingFrame, int maxDistance, int hue);
	void setIndex(int row, int col);
	void setHighlight(bool highlight);
	bool isHighlighted();
	void setDeleted(bool deleted);
	bool isDeleted();
	void setFalling(bool falling);
	bool isFalling();
	void instrumentOn();
	void instrumentOff();

private:
	// the array of chroma frequencies
	static const double freqs[12];

	// some representative data
	int tone;
	float freq;

	// some drawing specs
	int row, col;
	bool highlighted;
	bool falling;
	bool deleted;
	ofTrueTypeFont font;

	// the audio synthesizer
	stk::SineWave instrument;
};

#endif