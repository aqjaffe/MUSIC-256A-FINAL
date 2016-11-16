// FILE: Chroma.h
// AUTHOR: Adam Jaffe
// INFO: The header file for the Chroma class

#pragma once

#include <string>

class Chroma
{
public:
	Chroma();
	~Chroma();
	std::string getName();
	void setTone(int tone);

private:
	static const std::string names[12];
	int tone;
	int key;
};

