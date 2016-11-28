#include "ButtonZone.h"



ButtonZone::ButtonZone() {
	playButtonX = BUTTON_SIDE_MARGIN;
	playButtonY = BUTTON_TOP_MARGIN;
	int gap = 0.5 * ofGetWindowWidth() - BUTTON_SIDE_MARGIN - 1.5 * BUTTON_WIDTH;
	resetButtonX = BUTTON_SIDE_MARGIN + BUTTON_WIDTH + gap;
	resetButtonY = BUTTON_TOP_MARGIN;
	exportButtonX = BUTTON_SIDE_MARGIN + 2 * BUTTON_WIDTH + 2 * gap;
	exportButtonY = BUTTON_TOP_MARGIN;
}


ButtonZone::~ButtonZone() {}


void ButtonZone::draw(int x, int y) {
	ofRectangle playButton(x + playButtonX, y + playButtonY, BUTTON_WIDTH, BUTTON_HEIGHT);
	ofRectangle resetButton(x + resetButtonX, y + resetButtonY, BUTTON_WIDTH, BUTTON_HEIGHT);
	ofRectangle exportButton(x + exportButtonX, y + exportButtonY, BUTTON_WIDTH, BUTTON_HEIGHT);
	ofPushStyle();
	ofFill();
	ofSetColor(GRID_TILE_COLOR);
	ofDrawRectangle(playButton);
	ofDrawRectangle(resetButton);
	ofDrawRectangle(exportButton);
	ofNoFill();
	ofSetColor(GRID_BORDER_COLOR);
	ofDrawRectangle(playButton);
	ofDrawRectangle(resetButton);
	ofDrawRectangle(exportButton);
	ofPopStyle();
}


int ButtonZone::mousePressed(int x, int y) {
	if (BUTTON_TOP_MARGIN <= y && y <= BUTTON_TOP_MARGIN + BUTTON_HEIGHT) {
		if (playButtonX <= x && x <= playButtonX + BUTTON_WIDTH) {
			return 0;
		} else if (resetButtonX <= x && x <= resetButtonX + BUTTON_WIDTH) {
			return 1;
		} else if(exportButtonX <= x && x <= exportButtonX + BUTTON_WIDTH) {
			return 2;
		}
	}
	return -1;
}