// FILE: ChordList.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements ChordList, a class which keeps track of the selected chords


#include "ChordList.h"



ChordList::ChordList() {
	titleFont.loadFont("Comic Sans", 24);
	chordFont.loadFont("Verdana", 12);
	playingChord = -1;
}


ChordList::~ChordList() {
	for (int i = 0; i < chords.size(); i++) {
		delete chords.at(i);
		chords.erase(chords.begin() + i);
	}
}

void ChordList::addChord(PlayableChord* chord) {
	chords.push_back(chord);
}

int ChordList::getNumChords() {
	return chords.size();
}

void ChordList::draw(int x, int y) {
	ofPushStyle();
	std::string title = "Chords";
	ofSetColor(TITLE_FONT_COLOR);
	titleFont.drawString(title, x, y + titleFont.stringHeight(title));
	ofSetColor(CHORDS_FONT_COLOR);
	for (int i = 0; i < chords.size(); i++) {
		std::string chord = chords.at(i)->getChordName() + " ( " + chords.at(i)->getChromaNames() + ")";
		chordFont.drawString(chord, x, y + titleFont.stringHeight(title) + CHORD_LINE_SPACE
			+ (i + 1) * (chordFont.stringHeight(chord) + CHORD_LINE_SPACE));
	}
	ofPopStyle();
}

int ChordList::getPlayingChord() {
	return playingChord;
}

void ChordList::setPlayingChord(int chordIndex) {
	playingChord = chordIndex;
}

void ChordList::play(float* output, int bufferSize, int nChannels) {
	if (playingChord > -1) {
		chords.at(playingChord)->play(output, bufferSize, nChannels);
	}
}