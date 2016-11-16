// FILE: ChordList.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements ChordList, a class which keeps track of the selected chords


#include "ChordList.h"



ChordList::ChordList() {
	titleFont.loadFont("Comic Sans", 24);
	chordFont.loadFont("Verdana", 12);
}


ChordList::~ChordList() {
	//s
}

void ChordList::addChord(std::string chord) {
	chords.push_back(chord);
}

void ChordList::draw(int x, int y) {
	ofPushStyle();
	std::string title = "Chords";
	ofSetColor(TITLE_FONT_COLOR);
	titleFont.drawString(title, x, y + titleFont.stringHeight(title));
	ofSetColor(CHORDS_FONT_COLOR);
	for (int i = 0; i < chords.size(); i++) {
		std::string chord = chords.at(i);
		chordFont.drawString(chord, x, y + titleFont.stringHeight(title) + CHORD_LINE_SPACE
			+ (i + 1) * (chordFont.stringHeight(chord) + CHORD_LINE_SPACE));
	}
	ofPopStyle();
}
