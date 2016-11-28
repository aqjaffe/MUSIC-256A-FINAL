#ifndef CONSTANTS_H
#define CONSTANTS_H

// some audio parameters
#define SAMPLE_RATE 44100
#define BUFFER_SIZE 512
#define CHORD_DURATION_SCALE 0.75

#define DEFAULT_KEY 0
#define DEFAULT_TIME 120

// grid specs:

#define GRID_MARGIN 20
#define GRID_NBLOCKS 6
#define GRID_SIZE 500

// the falling speed of the blocks, in pxls/frame
#define GRAVITY 1

// chord list specs:

#define CHORDS_MARGIN 30
#define CHORDS_WIDTH 200
#define CHORD_LINE_SPACE 10

#define BUTTON_WIDTH 150
#define BUTTON_HEIGHT 80

// colors:

#define BACKGROUND_COLOR 0, 0, 0

#define GRID_BORDER_COLOR 0, 0, 0
#define GRID_TILE_COLOR 255, 243, 117
#define GRID_HIGHLIGHT_COLOR 255, 144, 117

// fonts:

#define GRID_FONT_NAME "Arial Black"
#define GRID_FONT_SIZE 14
#define GRID_FONT_COLOR 0, 0, 0

#define TITLE_FONT_NAME "Franklin Gothic Medium"
#define TITLE_FONT_SIZE 24
#define TITLE_FONT_COLOR 255, 255, 255

#define CHORDS_FONT_NAME "Franklin Gothic Medium"
#define CHORDS_FONT_SIZE 12
#define CHORDS_FONT_COLOR 255, 243, 147

#define BUTTON_SIDE_MARGIN 35
#define BUTTON_TOP_MARGIN 50

#define MAX_NCHROMA 5

#endif