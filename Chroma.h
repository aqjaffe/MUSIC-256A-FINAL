// FILE: Chroma.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Chroma class

#ifndef CHROMA_H
#define CHROMA_H

#define _USE_MATH_DEFINES
#include <math.h>
#include <string>
#include "Constants.h"

class Chroma
{
public:
	Chroma();
	~Chroma();
	std::string getName();
	float getFreq();
	void setTone(int tone);
	float tick();

private:
	static const std::string names[12];
	static const float freqs[12];
	int tone;
	std::string name;
	float freq;
	float currentAngle, angleDelta;
};

#endif