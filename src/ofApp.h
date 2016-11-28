// FILE: ofApp.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the ofApp class

//#pragma once

#ifndef OFAPP_H
#define OFAPP_H

#include <algorithm>
#include "ofMain.h"
#include "Grid.h"
#include "ChordList.h"
#include "ButtonZone.h"
//#include "FaustReverb.h"

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
	int score;
	float time_left;
	int key;
	Grid grid;
	ChordList chordList;
	ButtonZone buttonZone;
	int mousePressRow, mousePressCol;

	// the audio components

	ofSoundStream soundStream;
	int	bufferSize, sampleRate, nInputChans;

	vector <float> lAudio;
	vector <float> rAudio;

	//------------------- for Faust reverb stuff!
	float **audioBuffer; // The 2d audio buffer that Faust wants to work with

	//FaustReverb reverb; // the Faust module (FaustReverb.h)
	//MapUI reverbControl; // used to easily control the Faust module

	//ofMutex myMutex;

	bool mouseOverGrid(int x, int y);
	bool mouseOverPlayButton(int x, int y);
};

#endif