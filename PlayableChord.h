// FILE: Chord.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Chord class

#ifndef CHORD_H
#define CHORD_H

#include "Chroma.h"
#include "Constants.h"
#include <vector>
#include <string>

class PlayableChord {
public:
	PlayableChord();
	~PlayableChord();
	void addChroma(Chroma c);
	bool isDefined();
	std::string getChordName();
	std::string getChromaNames();
	void play(float* output, int bufferSize, int nChannels);

private:
	Chroma chroma[MAX_NCHROMA];
	int nChroma;
};

#endif