// FILE: Chroma.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements Chroma, a class used for representing tones without a specified octave

#include "Chroma.h"

// identifies integer and string representations of the same chroma
const std::string Chroma::names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};
const float Chroma::freqs[] = { 523.251, 554.365, 587.330, 622.254, 659.485,
								698.456, 739.989, 783.991, 830.609, 880.000,
								932.328, 987.767};

Chroma::Chroma() {
	tone = -1; //TODO: what should these be defined as? Should they be defined at all?
	name = "";
	freq = 0.0;
	currentAngle = 0.0;
	angleDelta = 0.0;

}


Chroma::~Chroma() {}

std::string Chroma::getName() {
	return name;
}

float Chroma::getFreq() {
	return freq;
}

void Chroma::setTone(int tone) {
	this->tone = tone;
	name = names[tone];
	freq = freqs[tone];
	angleDelta = freq * 2.0 * M_PI / (double)SAMPLE_RATE;
}

float Chroma::tick() {
	if (tone == -1) {
		//return an error
	} else {
		float currentSample = std::sin(currentAngle);
		currentAngle += angleDelta;
		return currentSample;
	}
}