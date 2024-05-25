#pragma once
#include <string>
#include <vector>


class DirectCode {
public:
	DirectCode(short number);

	std::string String();

	float Number();

	friend DirectCode operator*(DirectCode first, DirectCode second);

	friend DirectCode operator/(DirectCode first, DirectCode second);

	DirectCode operator=(const DirectCode& other);

	friend bool IsLess(DirectCode first, DirectCode second);

private:
	static void divisionPrePoint(DirectCode& remainder, DirectCode dividient, DirectCode divisor, DirectCode& output, int mostSignificantSize);
	static void divisionPostPoint(DirectCode& remainder, DirectCode dividient, DirectCode divisor, DirectCode& output);
	void insertBegin(int number);
	void substract(const DirectCode& other);
	void addOther(const DirectCode& other);
	std::vector<int> bit;
	const int size = 16;
	const int signlessSize = 15;
	const int pointSize = 21;
	const int signlessPointSize = 20;
	const int pointPos = 5;
};

