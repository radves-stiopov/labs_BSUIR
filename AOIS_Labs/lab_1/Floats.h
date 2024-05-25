#pragma once
#include <vector>
#include <string>

class Floats {
public:
	Floats(float number);
	std::string String();
	float Number();
	friend Floats operator+(Floats first, Floats second);
	
private:
	float getNumber(std::string intPart, std::string afterDot);
	int getExponentNumber();
	std::string getMantissaPartWithOne();
	static std::string makeExponentPart(int shiftCount);
	static std::string addBits(std::string first, std::string second, int& pointPos);
	static std::string addByPos(std::string first, std::string second, int& extra, int mostSize);
	static void shiftMantissas(std::string& firstMantissa, std::string& secondMantissa,
		int& firstExponent, int& secondExponent, int& expDiff);
	std::string bit;
	static int findFirstOne(std::string mantissa);
	static std::string partsToMantissa(int intPart, float floatPart, int& pointPos);
	static void mantissaFloat(std::string& mantissa, float floatPart);
	void partsToBits(bool isMinus, std::string exponentPart, std::string mantissa);
	const int mantissaSize = 23;
	const int size = 32;
	const int bias = 127;
	static const int exponentSize = 8;
};