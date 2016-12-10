// FILE: ChordID.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the ChordID class


#ifndef CHORDID_H
#define CHORDID_H

#include "Constants.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>

int interval(int bottom, int top);
std::string printChroma(std::vector<int> chord);
std::vector<int> getRootCandidates(std::vector<int> chord);
void filterRootCandidates(std::vector<int> chord, std::vector<int> & candidates);
int getRoot(std::vector<int> chord);
void getIntervals(int root, std::vector<int> chord, bool* intervals);
std::string getQualityFromIntervals(bool* intervals);
std::string getQuality(std::vector<int> chord, int root);
std::string chordName(std::vector<int> chord);
std::string chordNameFromRoot(std::vector<int> chord, int root);

#endif