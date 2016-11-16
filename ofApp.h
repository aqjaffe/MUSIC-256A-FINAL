// FILE: ofApp.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the ofApp class

#pragma once

#include <algorithm>
#include "ofMain.h"
#include "Grid.h"
#include "ChordList.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

private:
	int score;
	float time_left;
	int key;
	Grid grid;
	ChordList chordList;
	int mousePressRow, mousePressCol;

	bool mouseOverGrid(int x, int y);
};
