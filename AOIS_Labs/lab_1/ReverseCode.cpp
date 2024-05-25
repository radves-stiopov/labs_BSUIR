#include "ReverseCode.h"
#include <string>
#include <cmath>

ReverseCode::ReverseCode(short number) : bit(16, 0) {
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
		reverseBits();
	}
}

void ReverseCode::reverseBits() {
	for (int i = 0; i < signlessSize; i++) {
		bit[i] = bit[i] ? 0 : 1;
	}
}

std::string ReverseCode::String() {
	std::string output = "";
	for (int i = size - 1; i >= 0; i--) {
		output += std::to_string(bit[i]);
	}
	return output;
}

short ReverseCode::Number() {
	short output = 0;
	if (bit[signlessSize]) {
		reverseBits();
	}
	for (int i = 0; i < signlessSize; i++) {
		output += std::pow(2, i) * bit[i];
	}
	output *= (bit[signlessSize]) ? -1 : 1;
	if (bit[signlessSize]) {
		reverseBits();
	}
	return output;
}