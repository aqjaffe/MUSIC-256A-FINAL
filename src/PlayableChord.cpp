// FILE: Chord.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements Chord, which collects chroma into a playable chord


#include "PlayableChord.h"

PlayableChord::PlayableChord() {
	nChroma = 0;
	adsr.setAllTimes(ATTACK_TIME, DECAY_TIME, SUSTAIN_LEVEL, RELEASE_TIME);
	chorus.setSampleRate(SAMPLE_RATE);
	frame = -1;
}


PlayableChord::~PlayableChord() {}


void PlayableChord::addChroma(Chroma c) {
	if (nChroma < MAX_NCHROMA) {
		chroma[nChroma] = c;
		nChroma++;
	}
}


void PlayableChord::finalize() {
	std::vector<int> chord;
	for (int i = 0; i < nChroma; i++) chord.push_back(chroma[i].getTone());
	rootTone = getRoot(chord);
	root.setTone(rootTone, true);
	name = chordNameFromRoot(chord, rootTone);
}


bool PlayableChord::isDefined() {
	return nChroma >= 3;
}


void PlayableChord::chordOn(int millis) {
	nFramesPerPlay = SAMPLE_RATE * millis / (BUFFER_SIZE * 1000);
	nFramesUntilRelease = nFramesPerPlay - SAMPLE_RATE * RELEASE_TIME / BUFFER_SIZE;
	nFramesPerPlay *= 2;
	frame = 0;
	adsr.keyOn();
	for (int i = 0; i < nChroma; i++)
		chroma[i].instrumentOn();
	root.instrumentOn();
}


void PlayableChord::chordOff() {
	for (int i = 0; i < nChroma; i++)
		chroma[i].instrumentOff();
	root.instrumentOff();
}


string PlayableChord::getChordName() {
	return name;
}


string PlayableChord::getChromaNames() {
	string chromaNames = "";
	for (int i = 0; i < nChroma; i++)
		chromaNames += chroma[i].getName() + " ";
	return chromaNames;
}


PlayableChord* PlayableChord::compute(float* output, int bufferSize, int nChannels) {
	// the chroma values
	for (int sample = 0; sample < 2 * bufferSize; sample++)
		output[sample] = 0;
	for (int i = 0; i < nChroma; i++)
		chroma[i].tick(output, bufferSize);
	root.tick(output, bufferSize);
	for (int sample = 0; sample < 2 * bufferSize; sample++)
		output[sample] *= adsr.tick() / (float)(nChroma + 1.0);
	
	// the audio effect
	stk::StkFrames frames(bufferSize, 2);
	for (int i = 0; i < bufferSize; i++)
		frames(i, 0) = output[2 * i];
	stk::StkFrames effectOut(bufferSize, 2);
	chorus.tick(frames, effectOut, 0, 0);
	for (int i = 0; i < bufferSize; i++) {
		output[2 * i] = effectOut(i, 0);
		output[2 * i + 1] = effectOut(i, 1);
	}	
	
	// checking/updating the audio frames
	if (frame == nFramesPerPlay && adsr.getState() == stk::ADSR::IDLE) {
		chordOff();
		frame = -1;
		return NULL;
	} else if (frame > -1) {
		if (frame == nFramesUntilRelease)
			adsr.keyOff();
		frame++;
		return this;
	}
	else {
		return NULL;
	}
}


int PlayableChord::getTone() {
	return rootTone;
}


int PlayableChord::getRomanNumeral() {
	int interval = rootTone;
	if (interval == 0) return 1;
	else if (interval == 2) return 2;
	else if (interval == 4) return 3;
	else if (interval == 5) return 4;
	else if (interval == 7) return 5;
	else if (interval == 9) return 6;
	else return -1;

}