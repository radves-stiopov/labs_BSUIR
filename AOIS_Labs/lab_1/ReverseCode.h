#pragma once
#include <string>
#include <vector>

class ReverseCode {
public:
	ReverseCode(short number);
	std::string String();
	short Number();
private:
	void reverseBits();
	std::vector<int> bit;
	const int size = 16;
	const int signlessSize = 15;
};