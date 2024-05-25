#include "SupplementaryCode.h"
#include <string>
#include <cmath>

SupplementaryCode::SupplementaryCode(short number) : bit(16, 0) {
	bit[signlessSize] = (number < 0) ? 1 : 0;
	if (bit[signlessSize])
		number *= -1;

	for (int i = 0; i < signlessSize; i++) {
		int remainder = number % 2;
		if (remainder == 1) {
			bit[i] = 1;
		}
		number /= 2;
	}

	if (bit[signlessSize]) {
		SupplementaryCode oneInBits(1);
		reverseBits();
		addOther(oneInBits);
	}
}

void SupplementaryCode::addOther(const SupplementaryCode& other) {
	int extra = 0;

	for (int i = 0; i < size; i++) {
		int sumBits = bit[i] + other.bit[i] + extra;
		
		bit[i] = sumBits % 2;
		extra = sumBits / 2;
		if (sumBits == 0) {
			bit[i] = 0;
			extra = 0;
		}
		else if (sumBits == 1) {
			bit[i] = 1;
			extra = 0;
		}
		else if (sumBits == 2) {
			bit[i] = 0;
			extra = 1;
		}
		else {
			bit[i] = 1;
			extra = 1;
		}
	}
}

void SupplementaryCode::reverseBits() {
	for (int i = 0; i < signlessSize; i++) {
		bit[i] = bit[i] ? 0 : 1;
	}
}

std::string SupplementaryCode::String() {
	std::string output = "";
	for (int i = size - 1; i >= 0; i--) {
		output += std::to_string(bit[i]);
	}
	return output;
}

short SupplementaryCode::Number() {
	short output = 0;
	if (bit[signlessSize]) {
		SupplementaryCode oneInBits(1);
		reverseBits();
		addOther(oneInBits);
	}
	for (int i = 0; i < signlessSize; i++) {
		output += std::pow(2, i) * bit[i];
	}
	output *= (bit[signlessSize]) ? -1 : 1;
	if (bit[signlessSize]) {
		SupplementaryCode oneInBits(1);
		reverseBits();
		addOther(oneInBits);
	}
	return output;
}

SupplementaryCode::SupplementaryCode(const SupplementaryCode& other) : bit(16, 0) {
	for (int i = 0; i < size; i++) {
		bit[i] = other.bit[i];
	}
}

SupplementaryCode operator-(SupplementaryCode first, SupplementaryCode second) {
	SupplementaryCode output;
	output.addOther(first);
	second.bit[first.signlessSize] = (second.bit[first.signlessSize]) ? 0 : 1;
	second.reverseBits();
	SupplementaryCode oneInBits(1);
	second.addOther(oneInBits);
	output.addOther(second);
	return output;
}

SupplementaryCode operator+(SupplementaryCode first, SupplementaryCode second) {
	SupplementaryCode output;
	output.addOther(first);
	output.addOther(second);
	return output;
}