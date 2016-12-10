// FILE: Chord.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Chord class

#ifndef CHORD_H
#define CHORD_H

#include "ofxStk.h"
#include "Constants.h"
#include "ChordID.h"
#include "Chroma.h"
#include <vector>
#include <string>

class PlayableChord {
public:
	PlayableChord();
	~PlayableChord();
	void addChroma(Chroma c);
	void finalize();
	bool isDefined();
	void chordOn(int millis);
	void chordOff();
	std::string getChordName();
	std::string getChromaNames();
	int getTone();
	int getRomanNumeral();
	PlayableChord* compute(float* output, int bufferSize, int nChannels);

private:
	// the stored notes
	Chroma chroma[MAX_NCHROMA];
	Chroma root;

	// some other representative data
	int rootTone;
	string name;
	
	// some values for calculation
	int nChroma;
	int frame;
	int nFramesPerPlay;
	int nFramesUntilRelease;

	// some stk objects for audio effects
	stk::ADSR adsr;
	stk::Chorus chorus;
};

#endif