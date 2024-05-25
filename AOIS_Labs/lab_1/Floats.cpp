#include "Floats.h"
#include <iostream>

void Floats::mantissaFloat(std::string& mantissa, float floatPart) {
	int power = -1;
	int maxbits = 40;
	while (floatPart != 0.f || maxbits > 0) {
		float power2 = pow(2, power);
		if (power2 > floatPart) {
			mantissa += "0";
		}
		else {
			mantissa += "1";
			floatPart -= power2;
		}
		power--;
		maxbits--;
	}
}

std::string Floats::partsToMantissa(int intPart, float floatPart, int& pointPos) {
	int number = intPart + floatPart;
	std::string mantissa = "";
	mantissaFloat(mantissa, floatPart);
	int power = 0;
	while (number > pow(2, power) && power < 23) {
		power++;
	}
	power--;
	while (power >= 0) {
		int power2 = pow(2, power);
		if (power2 > intPart) {
			mantissa.insert(mantissa.begin() + pointPos, '0');
		}
		else {
			mantissa.insert(mantissa.begin() + pointPos, '1');
			intPart -= power2;
		}
		pointPos++;
		power--;
	}
	return mantissa;
}

Floats::Floats(float number) {
	bool isMinus = (number < 0) ? true : false;
	int intPart = (int)number;
	float floatPart = number - intPart;
	if (isMinus) {
		number *= -1;
	}
	int pointPos = 0;
	std::string mantissa = Floats::partsToMantissa(intPart, floatPart, pointPos);
	
	int firstOne = 0;
	for (int i = 0; i < mantissa.size(); i++) {
		if (mantissa[i] == '1') {
			firstOne = i + 1;
			break;
		}
	}
	int shiftCount = pointPos - firstOne;
	mantissa = mantissa.substr(pointPos - shiftCount, mantissaSize);

	shiftCount += bias;
	std::string exponentPart = makeExponentPart(shiftCount);
	partsToBits(isMinus, exponentPart, mantissa);
}

void Floats::partsToBits(bool isMinus, std::string exponentPart, std::string mantissa) {
	if (isMinus) {
		bit = "1";
	}
	else {
		bit = "0";
	}

	bit += exponentPart;
	bit += mantissa;
}

std::string Floats::makeExponentPart(int shiftCount) {
	std::string exponentPart = "";
	for (int i = 0; i < exponentSize; i++) {
		int remainder = shiftCount % 2;
		if (remainder == 1) {
			exponentPart.insert(exponentPart.begin(), '1');
		}
		else {
			exponentPart.insert(exponentPart.begin(), '0');
		}
		shiftCount /= 2;
	}
	return exponentPart;
}

std::string Floats::getMantissaPartWithOne() {
	std::string mantissaPart = bit.substr(exponentSize + 1, mantissaSize);
	mantissaPart.insert(mantissaPart.begin(), '1');
	return mantissaPart;
}

float Floats::getNumber(std::string intPart, std::string afterDot) {
	int intNumber = 0;
	int intPartSize = intPart.size();
	for (int i = intPartSize - 1; i >= 0; i--) {
		int bitPos = intPartSize - i - 1;
		intNumber += pow(2, bitPos) * (intPart[i] - '0');
	}

	float floatNumber = 0.f;
	for (int i = 0; i < afterDot.size(); i++) {
		int bitPos = i + 1;
		floatNumber += pow(2, -bitPos) * (afterDot[i] - '0');
	}
	return floatNumber + intNumber;
}

float Floats::Number() {
	std::string exponentPart = bit.substr(1, exponentSize);
	
	std::string mantissaPart = getMantissaPartWithOne();
	int exponent = getExponentNumber();
	exponent++;
	std::string intPart = "0";
	std::string afterDot = mantissaPart;
	if (exponent > 0) {
		intPart = mantissaPart.substr(0, exponent);
		afterDot = mantissaPart.substr(exponent, mantissaPart.size() - exponent);
	}
	else if (exponent < 0) {
		afterDot.insert(afterDot.begin(), '0');
	}
	
	return getNumber(intPart, afterDot);
}

int Floats::getExponentNumber() {
	int exponent = 0;
	for (int i = 1; i < exponentSize + 1; i++) {
		int bitPos = exponentSize - i;
		exponent += std::pow(2, bitPos) * (bit[i] - '0');
	}
	exponent -= 127;
	return exponent;
}

std::string Floats::String() {
	return bit;
}

void Floats::shiftMantissas(std::string& firstMantissa, std::string& secondMantissa,
	int& firstExponent, int& secondExponent, int& expDiff) {
	if (expDiff < 0) {
		expDiff = abs(expDiff);
		for (int i = 0; i < expDiff; i++) {
			firstMantissa.insert(firstMantissa.begin(), '0');
		}
		firstExponent = secondExponent;
	}
	else if (expDiff > 0) {
		for (int i = 0; i < expDiff; i++) {
			secondMantissa.insert(secondMantissa.begin(), '0');
		}
		secondExponent = firstExponent;
	}
}

int Floats::findFirstOne(std::string mantissa) {
	int firstOnePos = 0;
	for (int i = 0; i < mantissa.size(); i++) {
		if (mantissa[i] == '1') {
			firstOnePos = i;
			break;
		}
	}
	return firstOnePos;
}

Floats operator+(Floats first, Floats second) {
	int firstExponent = first.getExponentNumber();
	int secondExponent = second.getExponentNumber();
	std::string firstMantissa = first.getMantissaPartWithOne();
	std::string secondMantissa = second.getMantissaPartWithOne();

	int expDiff = firstExponent - secondExponent;
	Floats::shiftMantissas(firstMantissa, secondMantissa, firstExponent, secondExponent, expDiff);
	int pointPos = 0;
	
	std::string addedMantissa = Floats::addBits(firstMantissa, secondMantissa, pointPos);
	int firstOnePos = Floats::findFirstOne(addedMantissa);
	firstExponent += pointPos - firstOnePos + first.bias;
	std::string exponentPart = Floats::makeExponentPart(firstExponent);

	addedMantissa = addedMantissa.substr(firstOnePos + 1, first.mantissaSize);
	addedMantissa.resize(first.mantissaSize, '0');
	first.bit[0] = '0';
	std::copy(exponentPart.begin(), exponentPart.end(), first.bit.begin() + 1);
	std::copy(addedMantissa.begin(), addedMantissa.end(), first.bit.begin() + 9);
	return first;
}

std::string Floats::addBits(std::string first, std::string second, int& pointPos) {
	int mostSize = first.size() > second.size() ? first.size() : second.size();
	first.resize(mostSize, '0');
	second.resize(mostSize, '0');
	
	int extra = 0;
	std::string output = Floats::addByPos(first, second, extra, mostSize);
	if (extra == 1) {
		pointPos++;
		output.insert(output.begin(), static_cast<char>(extra + '0'));
	}
	return output;
}

std::string Floats::addByPos(std::string first, std::string second, int& extra, int mostSize) {
	std::string output;
	for (int i = mostSize - 1; i >= 0; i--) {
		int firstBit = first[i] - '0';
		int secondBit = second[i] - '0';
		int sumBits = firstBit + secondBit + extra;

		extra = sumBits / 2;
		if (sumBits == 0) {
			output.insert(output.begin(), '0');
			extra = 0;
		}
		else if (sumBits == 1) {
			output.insert(output.begin(), '1');
			extra = 0;
		}
		else if (sumBits == 2) {
			output.insert(output.begin(), '0');
			extra = 1;
		}
		else {
			output.insert(output.begin(), '1');
			extra = 1;
		}
	}
	return output;
}