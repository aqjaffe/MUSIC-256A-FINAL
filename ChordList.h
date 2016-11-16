// FILE: ChordList.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the ChordList class


#pragma once

#include <string>
#include <vector>
#include "ofMain.h"
#include "Constants.h"

class ChordList
{
public:
	ChordList();
	~ChordList();
	void addChord(std::string chord);
	void draw(int x, int y);

private:
	ofTrueTypeFont titleFont;
	ofTrueTypeFont chordFont;
	std::vector<std::string> chords;
};

