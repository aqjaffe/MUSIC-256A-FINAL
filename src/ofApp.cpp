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

	// below is copied from ofxFaust.sln:

	bufferSize = BUFFER_SIZE;
	sampleRate = SAMPLE_RATE;
	nInputChans = 2;
	//phase = 0;
	//phaseAdder = 0.1f;
	//phaseAdderTarget = 0.0f;
	//phaseAdderTarget = 0.0f;
	//volume = 0.1f;
	//bNoise = false;

	lAudio.assign(bufferSize, 0.0);
	rAudio.assign(bufferSize, 0.0);
	audioBuffer = new float*[2];
	audioBuffer[0] = &lAudio[0];
	audioBuffer[1] = &rAudio[0];

	//soundStream.printDeviceList();

	//if you want to set the device id to be different than the default
	//soundStream.setDeviceID(1); 	//note some devices are input only and some are output only 

	soundStream.setup(this, nInputChans, 0, sampleRate, bufferSize, 4);

	// setting default values for the Faust module parameters

	//reverbControl.setParamValue("/Zita_Rev1/Output/Level", -20);
	//reverbControl.setParamValue("/Zita_Rev1/Output/Dry/Wet_Mix", 0.0);
}

//--------------------------------------------------------------
void ofApp::update(){
	grid.update();
	chordList.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(BACKGROUND_COLOR);
	grid.draw(GRID_MARGIN, GRID_MARGIN, GRID_SIZE);
	chordList.draw(2 * GRID_MARGIN + GRID_SIZE + CHORDS_MARGIN, GRID_MARGIN);
	buttonZone.draw(0, 2 * GRID_MARGIN + GRID_SIZE);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (grid.isMoving() || chordList.isPlaying()) {
		return;
	}
	int row = (y - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
	int col = (x - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
	if (mouseOverGrid(x, y)) {
		grid.highlightBlocks(mousePressRow, mousePressCol, row, col);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int /* button */) {
	if (grid.isMoving() || chordList.isPlaying()) {
		return;
	}
	if (mouseOverGrid(x, y)) {
		mousePressRow = (y - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
		mousePressCol = (x - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
	} else if (y > 2 * GRID_MARGIN + GRID_SIZE) {
		int button = buttonZone.mousePressed(x, y - 2 * GRID_MARGIN - GRID_SIZE);
		if (button == 0) {
			chordList.playAllChords();
		} else if (button == 1) {
			chordList.resetChords();
		} else if (button == 2) {
			//export button
		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {
	if (grid.isMoving() || chordList.isPlaying()) {
		return;
	}
	PlayableChord* chord = grid.getHighlighted();
	if (chord->isDefined() && !chordList.isFull()) {
		chord->finalize();
		chordList.addChord(chord);
		grid.highlightErase();
	} else {
		delete chord;
		grid.highlightClear();
	}
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

bool ofApp::mouseOverPlayButton(int x, int y) {
	int buttonX = GRID_MARGIN * 2 + GRID_SIZE + CHORDS_MARGIN + 0.5 * (CHORDS_WIDTH - BUTTON_WIDTH);
	int buttonY = GRID_MARGIN + GRID_SIZE - CHORDS_MARGIN - BUTTON_HEIGHT;
	return buttonX < x && x < buttonX + BUTTON_WIDTH &&
		buttonY < y && y < buttonY + BUTTON_HEIGHT;
}

void ofApp::audioOut(float* output, int bufferSize, int nChannels) {
	chordList.compute(output, bufferSize, nChannels);

	/*

	//deinterleave the buffer
	for (int i = 0; i < bufferSize; i++) {
		lAudio[i] = output[i*nChannels];
		rAudio[i] = output[i*nChannels + 1];
	}

	// Faust stuff
	reverb.compute(bufferSize, audioBuffer, audioBuffer); // doesn't seem like this is doing anything to output

	// Interleave the output buffer
	for (int i = 0; i < bufferSize; i++)
	{
		output[2 * i] = lAudio[i]; //audioBuffer[0][i];
		output[2 * i + 1] = rAudio[i]; //audioBuffer[1][i];
	}

	*/
}