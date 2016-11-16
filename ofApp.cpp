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
}

//--------------------------------------------------------------
void ofApp::update(){
	//s
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofSetBackgroundColor(BACKGROUND_COLOR);
	grid.draw(GRID_MARGIN, GRID_MARGIN, GRID_SIZE);
	chordList.draw(2 * GRID_MARGIN + GRID_SIZE + CHORDS_MARGIN, GRID_MARGIN);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {
	if (mouseOverGrid(x, y)) {
		int row = (x - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
		int col = (y - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
		grid.highlightBlocks(mousePressRow, mousePressCol, row, col);
	}
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {
	if (mouseOverGrid(x, y)) {
		mousePressRow = (x - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;
		mousePressCol = (y - GRID_MARGIN) * GRID_NBLOCKS / GRID_SIZE;

	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
	std::string chord = grid.getHighlighted();
	if(std::count(chord.begin(), chord.end(), ' ') >= 3) chordList.addChord(chord);
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
