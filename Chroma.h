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

class Chroma
{
public:
	Chroma();
	~Chroma();
	std::string getName();
	int getTone();
	float getFreq();
	void setTone(int tone, bool low);
	float tick();
	void draw(int x, int y, int squareSide, int movingFrame, int maxDistance);
	void setIndex(int row, int col);
	void setHighlight(bool highlight);
	bool isHighlighted();
	void setDeleted(bool deleted);
	bool isDeleted();
	void setFalling(bool falling);
	bool isFalling();

private:
	// some const's for getting the name and freq of each tone
	static const std::string names[12];
	static const double freqs[12];

	int tone;
	std::string name;
	float freq;
	float currentAngle, angleDelta;

	// some drawing specs
	int row, col;
	bool highlighted;
	bool falling;
	bool deleted;

	ofTrueTypeFont font;
};

#endif