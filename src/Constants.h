#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

// some audio parameters

#define SAMPLE_RATE 44100
#define BUFFER_SIZE 512
#define ATTACK_TIME 0.10
#define DECAY_TIME 0.03
#define SUSTAIN_LEVEL 0.8
#define RELEASE_TIME 0.05
#define FILE_FREQUENCY 0.25

// some game element parameters

#define SECONDS_PER_KEY 60
#define CHORD_PLAYBACK_DURATION 500
#define MAX_NCHROMA 5

// some graphical parameters

#define GRAVITY 1
#define DEFAULT_COLOR 230, 230, 230
#define GRID_X 225
#define GRID_Y 25
#define GRID_SIZE 550
#define GRID_NBLOCKS 6
#define CHROMA_FONT_NAME "OCR A Extended"
#define CHROMA_FONT_SIZE 24
#define GAME_FONT_NAME "OCR A Extended"
#define GAME_FONT_SIZE 36
#define KEY_FONT_SIZE 58
#define MESSAGE_FONT_SIZE 18
#define SATURATION 180
#define BRIGHTNESS 180

extern int key;

extern int level;

const std::string names[][12] =
{ { "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "Bb", "B" }, // C
{ "Db", "D", "Eb", "E", "F", "Gb", "G", "Ab", "A", "Bb", "Cb", "C" }, // Db
{ "D", "D#", "E", "E#", "F#", "G", "G#", "A", "A#", "B", "C", "C#" }, // D
{ "Eb", "E", "F", "F#", "G", "Ab", "A", "Bb", "B", "C", "Db", "D" }, // Eb
{ "E", "E#", "F#", "F##", "G#", "A", "A#", "B", "B#", "C#", "D", "D#" }, // E
{ "F", "F#", "G", "G#", "A", "Bb", "B", "C", "C#", "D", "Eb", "E" }, // F
{ "Gb", "G", "Ab", "A", "Bb", "Cb", "C", "Db", "D", "Eb", "Fb", "F" }, // Gb
{ "G", "G#", "A", "A#", "B", "C", "C#", "D", "D#", "E", "F", "F#" }, // G
{ "Ab", "A", "Bb", "B", "C", "Db", "D", "Eb", "E", "F", "Gb", "G" }, // Ab
{ "A", "A#", "B", "B#", "C#", "D", "D#", "E", "E#", "F#", "G", "G#" }, // A
{ "Bb", "B", "C", "C#", "D", "Eb", "E", "F", "F#", "G", "Ab", "A" }, // Bb
{ "B", "B#", "C#", "C##", "D#", "E", "E#", "F#", "F##", "G#", "A", "A#" }, // B
};

#endif