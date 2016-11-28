// FILE: ChordList.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the ChordList class

#ifndef CHORDLIST_H
#define CHORDLIST_H

#include "PlayableChord.h"
#include <string>
#include <vector>
#include "ofMain.h"
#include "Constants.h"

class ChordList {
public:
	ChordList();
	~ChordList();
	void addChord(PlayableChord* chord);
	int getNumChords();
	void update();
	void draw(int x, int y);
	int getPlayingChord();
	void setPlayingChord(int chordIndex);
	void playAllChords();
	void resetChords();
	void compute(float* output, int bufferSize, int nChannels);
	bool isPlaying();
	bool isFull();

private:
	ofTrueTypeFont titleFont;
	ofTrueTypeFont chordFont;
	std::vector<PlayableChord*> chords;
	int playingChord;
	ofRectangle button;
	int nBuffersPerPlay;
	int nBuffer;
	int nChordsDisplay;
};

#endif