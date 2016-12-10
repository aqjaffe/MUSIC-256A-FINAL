// FILE: ofApp.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements ofApp, a class which contains the program to be run

#include "ofApp.h"

extern int key(rand() % 12);

extern int level(1);

void ofApp::setup() {
	// initialize the game values
	score = 0;
	playingChord = NULL;
	mousePressRow = -1;
	mousePressCol = -1;
	gameTime = SECONDS_PER_KEY;
	firstRun = true;
	gameLost = false;
	prevChord = -1;

	// set up the graphical elements
	gameStart = std::clock();
	keyStart = std::clock();
	message = "";
	cadence = "";
	image.load("CrosschordBackground.png");
	smooth.setSmooth(0.94);
	font.loadFont(GAME_FONT_NAME, GAME_FONT_SIZE);
	messageFont.loadFont(GAME_FONT_NAME, MESSAGE_FONT_SIZE);
	keyFont.loadFont(GAME_FONT_NAME, KEY_FONT_SIZE);
	titleFont.loadFont(GAME_FONT_NAME, 60);

	// set up the audio elements
	bufferSize = BUFFER_SIZE;
	sampleRate = SAMPLE_RATE;
	nInputChans = 2;
	soundStream.setup(this, nInputChans, 0, sampleRate, bufferSize, 4);
	beat.setFrequency(FILE_FREQUENCY);
	stk::Stk::setSampleRate(SAMPLE_RATE);
}


void ofApp::update(){
	grid.update();
	std::clock_t curr = std::clock();
	if ((curr - gameStart) / (float)CLOCKS_PER_SEC >= gameTime) {
		gameLost = true;
	} else if ((curr - keyStart) / (float)CLOCKS_PER_SEC >= SECONDS_PER_KEY) { // reset the key
		keyStart = curr;
		int newKey;
		do {
			newKey = rand() % 12;
		} while (newKey == ::key);
		::key = newKey;
		::key %= 12;
		::level++;
		grid.reset();
		message = "";
		prevChord = -1;
	}
}


void ofApp::draw() {
	// draw the background and grid
	hue = smooth.tick(255 * ::key / 12.0);
	ofSetBackgroundColor(ofColor::fromHsb(hue, SATURATION, BRIGHTNESS));
	image.draw(0, 0);
	if (gameLost || firstRun) {
		titleFont.drawString("crosschord", 250, 100);
		font.drawString("TIME", 55, 70);
		font.drawString("SCORE", 40, 165);
		keyFont.loadFont(GAME_FONT_NAME, KEY_FONT_SIZE);
		keyFont.drawString("KEY", 45, 535);
		if (firstRun) {
			messageFont.drawString("Select 3 to 5 notes to make a chord."
				"\n\nGain points and extra time for"
				"\npicking chords from the given key."
				"\n\n60 sec per key."
				"\n60 on the clock to play.", 250, 200);
			messageFont.drawString("Click anywhere to play", 340, 500);
		}
		else {
			messageFont.drawString("GAME OVER", 440, 300);
			string scoreStr = "Score: " + to_string(score);
			messageFont.drawString(scoreStr, 225 + 0.5 * (GRID_SIZE - messageFont.stringWidth(scoreStr)), 350);
			messageFont.drawString("Click anywhere to replay", 340, 500);
		}
		return;
	}
	grid.draw(GRID_X, GRID_Y, GRID_SIZE, hue);

	// draw the timer
	ofSetColor(DEFAULT_COLOR);
	float time = gameTime - (std::clock() - gameStart) / (float)CLOCKS_PER_SEC;
	string timeStr;
	if (time >= 10.0) timeStr = to_string(time).substr(0, 5);
	else timeStr = "0" + to_string(time).substr(0, 4);
	font.drawString(timeStr, 38, 70);

	// draw the sidebar elements
	string scoreName = to_string(score);
	font.drawString(scoreName, 20 + 0.5 * (175 - font.stringWidth(scoreName)), 165);
	string keyName = names[::key][0];
	messageFont.drawString(message, 20 + 0.5 * (175 - messageFont.stringWidth(message)), 265);
	if (!cadence.empty()) {
		messageFont.drawString(cadence, 20 + 0.5 * (175 - messageFont.stringWidth(cadence)), 300);
		messageFont.drawString("Cadence", 20 + 0.5 * (175 - messageFont.stringWidth("Cadence")), 330);
	}
	ofPushStyle();
	float timeKeyProportion = (std::clock() - keyStart) / (float)(CLOCKS_PER_SEC * SECONDS_PER_KEY);
	ofSetColor(DEFAULT_COLOR, 255 * (1 -timeKeyProportion));
	keyFont.drawString(keyName, 20 + 0.5 * (175 - keyFont.stringWidth(keyName)), 435 + 0.5 * (140 + keyFont.stringHeight(keyName)));
	ofPopStyle();
}


void ofApp::keyPressed(int key) {}


void ofApp::keyReleased(int key) {}


void ofApp::mouseMoved(int x, int y) {}


void ofApp::mouseDragged(int x, int y, int button) {
	if (grid.isMoving()) return;
	int col = (x - GRID_X) * GRID_NBLOCKS / GRID_SIZE;
	int row = (y - GRID_Y) * GRID_NBLOCKS / GRID_SIZE;
	if (mouseOverGrid(x, y)) grid.highlightBlocks(mousePressRow, mousePressCol, row, col);
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int /* button */) {
	if (gameLost || firstRun) {
		gameLost = false;
		firstRun = false;
		score = 0;
		playingChord = NULL;
		prevChord = -1;
		gameTime = SECONDS_PER_KEY;
		gameStart = std::clock();
		keyStart = std::clock();
		::key = rand() % 12;
		grid.reset();
	} else if (grid.isMoving()) return;
	else if (mouseOverGrid(x, y)) {
		mousePressCol = (x - GRID_X) * GRID_NBLOCKS / GRID_SIZE;
		mousePressRow = (y - GRID_Y) * GRID_NBLOCKS / GRID_SIZE;
		grid.highlightBlocks(mousePressRow, mousePressCol, mousePressRow, mousePressCol);
	}
}


void ofApp::mouseReleased(int x, int y, int button) {
	if (grid.isMoving() || playingChord != NULL) return;
	PlayableChord* chord = grid.getHighlighted();
	if (chord->isDefined()) {
		// set the chord to play
		chord->finalize();
		delete playingChord;
		playingChord = chord;
		playingChord->chordOn(CHORD_PLAYBACK_DURATION);
		grid.highlightErase();

		// update the score and message box
		message = playingChord->getChordName();
		int pts = playingChord->getScore();
		if (pts > 0) {
			gameTime += 2;
			score += pts;
		}
		else {
			message = "";
		}
		playingChord->getChromaNames();
		int roman = playingChord->getRomanNumeral();
		if (prevChord == 5 && roman == 1) { // authentic cadence
			cadence = "Authentic";
			score += 50;
			gameTime += 5;
		}
		else if (prevChord == 4 && roman == 1) { // plagal cadence
			cadence = "Plagal";
			score += 30;
			gameTime += 5;
		}
		else if (prevChord == 5 && roman == 6) { // deceptive cadence
			cadence = "Deceptive";
			score += 40;
			gameTime += 5;
		}
		else {
			cadence = "";
		}
		if (pts < 0) prevChord = -1;
		else prevChord = roman;
	} else {
		delete chord;
		grid.highlightClear();
	}
}


void ofApp::mouseEntered(int x, int y) {}


void ofApp::mouseExited(int x, int y) {}


void ofApp::windowResized(int w, int h) {}


void ofApp::gotMessage(ofMessage msg) {}

void ofApp::dragEvent(ofDragInfo dragInfo) {}

bool ofApp::mouseOverGrid(int x, int y) {
	return GRID_X < x && x < GRID_X + GRID_SIZE &&
		GRID_Y < y && y < GRID_Y + GRID_SIZE;
}

void ofApp::audioOut(float* output, int bufferSize, int nChannels) {
	if (playingChord != NULL) playingChord = playingChord->compute(output, bufferSize, nChannels);
}