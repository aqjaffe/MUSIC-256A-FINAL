# MUSIC-256A-FINAL
My final project for MUSIC 256A!

This program is an educational tool to teach people about chord sequences. In the game, one can select linear blocks of notes from the displayed grid and the program will determine the chord formed by these notes. The game is won by making chord sequences that make sense.

I spent a great deal of time working on the chord naming algorithm. The chordID program takes a vector of integers between 0 and 12 representing chroma and determines the name of ther resulting chord by finding its (1) root, (2) quality, and (3) color.

The most difficult task is (1) finding the root. To do so, I rank every note in the chord by the number of thirds (minor or major) and fifths (flat, perfect, or sharp) above it. This leaves a resulting set of candidates, which is usually fairly small. To narrow down even further, I remove any candidates which is a third or a fifth above another candidates. If there are still multiple root candidates, then we select one at random.

To (2) determine quality, I simply check a series of cases about which thirds and fifths are present, and this leads to the quality.

Color (3) has not yet been implemented, and it may prove a difficult task.


Created using VisualStudio2015 and openFrameworks. Created for MUSIC 256A at Stanford CCRMA.
