// FILE: ofApp.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the ofApp class

#ifndef OFAPP_H
#define OFAPP_H

#include "ofMain.h"
#include "ofxStk.h"
#include "Grid.h"
#include "Smooth.h"
#include <algorithm>
#include <random>
#include <vector>
#include <ctime>


class ofApp : public ofBaseApp {

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
		void audioOut(float * output, int bufferSize, int nChannels);

private:
	// some game elements
	Grid grid;
	PlayableChord* playingChord;
	int prevChord;
	int score;
	int hue;
	Smooth smooth;
	int mousePressRow, mousePressCol;
	float gameTime;
	bool firstRun;
	bool gameLost;

	// some graphical elements
	clock_t gameStart;
	clock_t keyStart;
	string message;
	string cadence;
	ofImage image;
	ofTrueTypeFont font;
	ofTrueTypeFont keyFont;
	ofTrueTypeFont messageFont;
	ofTrueTypeFont titleFont;

	// some audio elements
	int	bufferSize, sampleRate, nInputChans;
	ofSoundStream soundStream;
	stk::FileLoop beat;

	bool mouseOverGrid(int x, int y);
};

#endif