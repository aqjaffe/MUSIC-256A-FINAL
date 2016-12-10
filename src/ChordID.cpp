// FILE: ChordID.cpp
// AUTHOR: Adam Jaffe
// INFO: Implements ChordID, toolkit for chord identification


#include "ChordID.h"


int interval(int bottom, int top) {
	int output = top - bottom;
	output %= 12;
	if (output < 0) output += 12;
	return output;
}

std::string printChroma(std::vector<int> chord) {
	std::string output = "";
	for (unsigned i = 0; i < chord.size(); i++) output += names[::key][chord[i]] + " ";
	return output;
}

/* Rank each note by the number of thirds and fifths above it,
and return a vector of the top canidates. */
std::vector<int> getRootCandidates(std::vector<int> chord) {
	std::vector<int> candidates;
	int maxScore = -1;
	for (std::vector<int>::iterator it = chord.begin(); it < chord.end(); ++it) {
		int score = 0;
		if (find(chord.begin(), chord.end(), (*it + 3) % 12) != chord.end()
			|| find(chord.begin(), chord.end(), (*it + 4) % 12) != chord.end()) score++;
		if (find(chord.begin(), chord.end(), (*it + 7) % 12) != chord.end()) score++;
		if (score > maxScore) {
			candidates.clear();
			candidates.push_back(*it);
			maxScore = score;
		}
		else if (score == maxScore) {
			candidates.push_back(*it);
		}
	}
	return candidates;
}

/* Remove any candidate which is a third or a fifth above another candidate. */
void filterRootCandidates(std::vector<int> chord, std::vector<int> & candidates) {
	std::vector<int> filtered;
	for (std::vector<int>::iterator it = candidates.begin(); it < candidates.end(); ++it) {
		bool remove = false;
		for (std::vector<int>::iterator otherIt = candidates.begin(); otherIt < candidates.end(); ++otherIt) {
			int i = interval(*otherIt, *it);
			if (i == 3 || i == 4 || i == 6 || i == 7 || i == 8) {
				remove = true;
				break;
			}
		}
		if (!remove) {
			filtered.push_back(*it);
		}
	}
	if (filtered.size() != 0) {
		candidates = filtered;
	}
}

/* Return the most likely root for the given chord. */
int getRoot(std::vector<int> chord) {
	std::vector<int> candidates = getRootCandidates(chord);
	filterRootCandidates(chord, candidates);
	//if there are multiple candidates, randomly select one.
	return candidates[(int)(candidates.size() * rand() / (float)RAND_MAX)];
}

/* Write true to intervals[n] iffthere is a note an nth interval up from root. */
void getIntervals(int root, std::vector<int> chord, bool* intervals) {
	for (std::vector<int>::iterator it = chord.begin(); it < chord.end(); ++it) {
		intervals[interval(root, *it)] = true;
	}
}

/* Determine the chord quality from the boolean array. */
std::string getQualityFromIntervals(bool* intervals) {
	std::string quality;
	if (intervals[7]) {
		if (intervals[3]) quality = "minor";
		else if (intervals[4]) quality = "major";
		else quality = "";
	}
	else if (intervals[6]) quality = "diminished";
	else if (intervals[8]) quality = "augmented";
	else if (intervals[3]) quality = "minor";
	else if (intervals[4]) quality = "major";
	else quality = "";
	return quality;
}

/* Return the string for the quality of the chord. */
std::string getQuality(std::vector<int> chord, int root) {
	bool intervals[12] = { false };
	getIntervals(root, chord, intervals);
	return getQualityFromIntervals(intervals);
}

/* Returns the string for the name of the given chord. */
std::string chordName(std::vector<int> chord) {
	int root = getRoot(chord);
	std::string quality = getQuality(chord, root);
	std::string name = names[::key][root] + " " + quality;
	return name;
}

/* Returns the string for the name of the given chord, with the specified root. */
std::string chordNameFromRoot(std::vector<int> chord, int root) {
	std::string quality = getQuality(chord, root);
	// TODO: record color notes
	std::string name = names[::key][root] + " " + quality;
	return name;
}
