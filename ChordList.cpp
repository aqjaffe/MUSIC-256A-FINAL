// FILE: ChordList.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements ChordList, a class which keeps track of the selected chords


#include "ChordList.h"



ChordList::ChordList() {
	titleFont.loadFont(TITLE_FONT_NAME, TITLE_FONT_SIZE);
	chordFont.loadFont(CHORDS_FONT_NAME, CHORDS_FONT_SIZE);
	playingChord = -1;
	nBuffersPerPlay = SAMPLE_RATE / BUFFER_SIZE * CHORD_DURATION_SCALE;
	nBuffer = -1;
	int chordHeight = chordFont.stringHeight("chord") + CHORD_LINE_SPACE;
	int verticalSpace = GRID_SIZE - titleFont.stringHeight("Chords")
		- 4 * CHORD_LINE_SPACE - 3 * chordFont.stringHeight("Cmaj7 ( C E G B )");
	nChordsDisplay = verticalSpace / chordHeight;
}


ChordList::~ChordList() {
	resetChords();
}

void ChordList::addChord(PlayableChord* chord) {
	chords.push_back(chord);
}

int ChordList::getNumChords() {
	return chords.size();
}


void ChordList::update() {
	if (nBuffer == nBuffersPerPlay) {
		if (playingChord == chords.size() - 1) {
			playingChord = -1;
			nBuffer = -1;
		} else {
			playingChord++;
			nBuffer = 0;
		}
	} else if (nBuffer > -1) {
		nBuffer++;
	}
}


void ChordList::draw(int x, int y) {
	ofPushStyle();
	std::string title = "Chords";
	ofSetColor(TITLE_FONT_COLOR);
	titleFont.drawString(title, x, y + titleFont.stringHeight(title));
	for (int i = 0; i < chords.size(); i++) {
		if (playingChord == i) ofSetColor(GRID_HIGHLIGHT_COLOR);
		else ofSetColor(CHORDS_FONT_COLOR);
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


void ChordList::playAllChords() {
	if (chords.size() > 0) {
		nBuffer = 0;
		playingChord = 0;
	}
}


void ChordList::resetChords() {
	int size = chords.size();
	for (int i = 0; i < size; i++) {
		delete chords.at(i);
	}
	chords.erase(chords.begin(), chords.end());
}


void ChordList::compute(float* output, int bufferSize, int nChannels) {
	if (playingChord > -1) {
		chords.at(playingChord)->play(output, bufferSize, nChannels);
	}
}


bool ChordList::isPlaying() {
	return nBuffer > -1;
}

bool ChordList::isFull() {
	return chords.size() == nChordsDisplay;
}