// FILE: Chord.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements Chord, which collects chroma into a playable chord


#include "PlayableChord.h"

PlayableChord::PlayableChord() {
	nChroma = 0;
}

PlayableChord::~PlayableChord() {
	//s
}

void PlayableChord::addChroma(Chroma c) {
	if (nChroma < MAX_NCHROMA) {
		chroma[nChroma] = c;
		nChroma++;
	}
}


bool PlayableChord::isDefined() {
	return nChroma >= 3;
}

std::string PlayableChord::getChordName() {
	std::string name = "";
	name = "adam"; //TODO: change this
	return name;
}


std::string PlayableChord::getChromaNames() {
	std::string chromaNames = "";
	for (int i = 0; i < nChroma; i++) {
		chromaNames += chroma[i].getName() + " ";
	}
	return chromaNames;
}


void PlayableChord::play(float* output, int bufferSize, int nChannels) {
	for (int sample = 0; sample < bufferSize; sample++) {
		float total = 0.0;
		for (int i = 0; i < nChroma; i++) {
			total += chroma[i].tick();
		}
		float val = (float)(total / (float)nChroma);
		for (int chan = 0; chan < nChannels; chan++) {
			output[sample * nChannels + chan] = val;
		}
	}
}