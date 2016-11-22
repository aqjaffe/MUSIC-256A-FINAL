// FILE: ofApp.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements ofApp, a class which contains the program to be run

#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	score = 0;
	time_left = DEFAULT_TIME;
	key = DEFAULT_KEY;

	mousePressRow = -1;
	mousePressCol = -1;

	moving = false;

	// below is copied from ofxFaust.sln:

	int bufferSize = 512;
	sampleRate = 44100;
	nInputChans = 2;
	//phase = 0;
	//phaseAdder = 0.1f;
	//phaseAdderTarget = 0.0f;
	//phaseAdderTarget = 0.0f;
	//volume = 0.1f;
	//bNoise = false;

	//lAudio.assign(bufferSize, 0.0);
	//rAudio.assign(bufferSize, 0.0);
	//audioBuffer = new float*[2];
	//audioBuffer[0] = &lAudio[0];
	//audioBuffer[1] = &rAudio[0];

	//soundStream.printDeviceList();

	//if you want to set the device id to be different than the default
	//soundStream.setDeviceID(1); 	//note some devices are input only and some are output only 

	soundStream.setup(this, nInputChans, 0, sampleRate, bufferSize, 4);
}

//--------------------------------------------------------------
void ofApp::update(){
	if (moving) {
		//s
		moving = false;
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(BACKGROUND_COLOR);
	grid.draw(GRID_MARGIN, GRID_MARGIN, GRID_SIZE);
	chordList.draw(2 * GRID_MARGIN + GRID_SIZE + CHORDS_MARGIN, GRID_MARGIN);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 's') {
		chordList.setPlayingChord(chordList.getNumChords() - 1);
	} else if (key == 'e') {
		chordList.setPlayingChord(-1);
	} else if (key == 'p') {
		//s
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (moving) {
		return;
	} else if (mouseOverGrid(x, y)) {
		int row = (x - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
		int col = (y - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
		grid.highlightBlocks(mousePressRow, mousePressCol, row, col);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (moving) {
		return;
	} else if (mouseOverGrid(x, y)) {
		mousePressRow = (x - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
		mousePressCol = (y - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	if (moving) {
		return;
	}
	PlayableChord* chord = grid.getHighlighted(); // needs to be deallocated!
	if (chord->isDefined()) {
		chordList.addChord(chord);
	}
	moving = true;
	grid.highlightClear();
}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

bool ofApp::mouseOverGrid(int x, int y) {
	return GRID_MARGIN < x && x < GRID_MARGIN + GRID_SIZE &&
		GRID_MARGIN < y && y < GRID_MARGIN + GRID_SIZE;
}

void ofApp::audioOut(float* output, int bufferSize, int nChannels) {
	chordList.play(output, bufferSize, nChannels);
}