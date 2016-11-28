#ifndef BUTTONZONE_H
#define BUTTONZONE_H

#include "ofMain.h"
#include "Constants.h"

class ButtonZone {
public:
	ButtonZone();
	~ButtonZone();
	void draw(int x, int y);
	int mousePressed(int x, int y);

private:
	int playButtonX, playButtonY;
	int resetButtonX, resetButtonY;
	int exportButtonX, exportButtonY;
};

#endif