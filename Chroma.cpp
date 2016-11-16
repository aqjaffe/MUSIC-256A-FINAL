// FILE: Chroma.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements Chroma, a class used for representing tones without a specified octave

#include "Chroma.h"

// identifies integer and string representations of the same chroma
const std::string Chroma::names[] = {"C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "Bb", "B"};

Chroma::Chroma() {
	this->tone = -1;
}


Chroma::~Chroma() {
	//s
}

std::string Chroma::getName() {
	return names[tone];
}

void Chroma::setTone(int tone) {
	this->tone = tone;
}
