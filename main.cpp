#include "ofMain.h"
#include "ofApp.h"
#include "Constants.h"

//========================================================================
int main( ){
	ofSetupOpenGL(2 * GRID_MARGIN + GRID_SIZE + 2 * CHORDS_MARGIN + CHORDS_WIDTH,
		2 * GRID_MARGIN + GRID_SIZE + 2 * BUTTON_TOP_MARGIN + BUTTON_HEIGHT, OF_WINDOW);

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp(new ofApp());

}
