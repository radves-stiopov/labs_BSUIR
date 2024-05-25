#include "DirectCode.h"
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

DirectCode::DirectCode(short number) : bit(16, 0) {
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
}

std::string DirectCode::String() {
	std::string output = "";
	int i = 0;
	if (bit.size() == size) {
		i = size - 1;
	}
	else {
		i = pointSize - 1;
	}

	while (i >= 0) {
		output += std::to_string(bit[i--]);
	}
	
	return output;
}

float DirectCode::Number() {
	float output = 0;
	if (bit.size() == size) {
		for (int i = 0; i < signlessSize; i++) {
			output += std::pow(2, i) * bit[i];
		}
		output *= (bit[signlessSize]) ? -1 : 1;
	}
	else {
		for (int i = pointPos; i < signlessPointSize; i++) {
			output += std::pow(2, (i - 5)) * bit[i];
		}
		for (int i = 0; i < pointPos; i++) {
			output += std::pow(2, -(5 - i)) * bit[i];
		}
		output *= (bit[signlessSize]) ? -1 : 1;
	}
	return output;
}

DirectCode operator*(DirectCode first, DirectCode second) {
	bool minus = (first.bit[first.signlessSize] != second.bit[second.signlessSize]) ? true : false;
	int bitsCount = first.signlessSize;
	DirectCode output(0);
	DirectCode shiftedPart(0);
	while (bitsCount >= 0) {
		if (second.bit[bitsCount] == 1) {
			std::copy(first.bit.begin(), first.bit.end() - bitsCount, shiftedPart.bit.begin() + bitsCount);
			output.addOther(shiftedPart);
			std::fill(shiftedPart.bit.begin(), shiftedPart.bit.end(), 0);
		}
		bitsCount--;
	}
	if (minus) {
		output.bit[first.signlessSize] = 1;
	}
	return output;
}

void DirectCode::divisionPrePoint(DirectCode& remainder, DirectCode dividient, DirectCode divisor, DirectCode& output, int mostSignificantSize) {
	remainder.insertBegin(0);
	for (int i = 0; i < mostSignificantSize; i++) {
		remainder.insertBegin(dividient.bit[mostSignificantSize - i - 1]);
		if (IsLess(remainder, divisor)) {
			output.insertBegin(0);
		}
		else {
			output.insertBegin(1);
			remainder.substract(divisor);
		}
	}
}

void DirectCode::divisionPostPoint(DirectCode& remainder, DirectCode dividient, DirectCode divisor, DirectCode& output) {
	for (int i = 0; i < 5; i++) {
		remainder.insertBegin(0);
		if (IsLess(remainder, divisor)) {
			output.insertBegin(0);
		}
		else {
			output.insertBegin(1);
			remainder.substract(divisor);
		}
	}
}

DirectCode operator/(DirectCode dividient, DirectCode divisor) {
	bool minus = (dividient.bit[dividient.signlessSize] != divisor.bit[divisor.signlessSize]) ? true : false;
	dividient.bit[dividient.signlessSize] = 0;
	divisor.bit[divisor.signlessSize] = 0;
	DirectCode remainder(0);
	DirectCode output(0);
	output.bit.resize(output.pointSize, 0);
	int mostSignificantSize = 0;
	for (int i = dividient.signlessSize; i >= 0; i--) {
		if (dividient.bit[i] == 1) {
			mostSignificantSize = i + 1;
			break;
		}
	}
	DirectCode::divisionPrePoint(remainder, dividient, divisor, output, mostSignificantSize);
	DirectCode::divisionPostPoint(remainder, dividient, divisor, output);
	
	if (minus) {
		output.bit[output.signlessSize] = 1;
	}
	return output;
}

void DirectCode::insertBegin(int number) {
	std::copy(bit.begin(), bit.end() - 1, bit.begin() + 1);
	bit[0] = number;
}

void DirectCode::substract(const DirectCode& other) {
	int extra = 0;
	DirectCode output(0);
	int nextPos = 0;
	int mostSignificantSize = 0;
	for (int i = signlessSize; i >= 0; i--) {
		if (bit[i] == 1 || other.bit[i] == 1) {
			mostSignificantSize = i;
		}
	}
	
	for (int i = 0; i < size; i++) {
		int dif = bit[i] - other.bit[i] - extra;
		if (dif < 0) {
			dif += 2;
			extra = 1;
		}
		else {
			extra = 0;
		}
		output.bit[nextPos++] = dif;
	}

	std::copy(output.bit.begin(), output.bit.end(), bit.begin());
}

bool IsLess(DirectCode first, DirectCode second) {
	for (int i = first.signlessSize; i >= 0; i--) {
		if (first.bit[i] > second.bit[i]) {
			return false;
		}
		else if (first.bit[i] < second.bit[i]) {
			return true;
		}
	}

	return false;
}

void DirectCode::addOther(const DirectCode& other) {
	int extra = 0;

	for (int i = 0; i < size; i++) {
		int sumBits = bit[i] + other.bit[i] + extra;

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