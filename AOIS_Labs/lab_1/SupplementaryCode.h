#pragma once
#include <vector>
#include <string>

class SupplementaryCode {
public:
	short Number();

	SupplementaryCode(short number);

	SupplementaryCode(const SupplementaryCode& other);
	
	SupplementaryCode() : bit(16, 0) { }

	std::string String();

	friend SupplementaryCode operator-(SupplementaryCode first, SupplementaryCode second);
	friend SupplementaryCode operator+(SupplementaryCode first, SupplementaryCode second);
private:
	void reverseBits();

	void addOther(const SupplementaryCode& other);

	std::vector<int> bit;
	const int size = 16;
	const int signlessSize = 15;
};