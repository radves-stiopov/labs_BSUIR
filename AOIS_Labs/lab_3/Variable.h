#pragma once
#include <string>

class Variable {
public:
	Variable(char character, bool isPositive);
	bool Equals(const Variable& other) const;
	std::string ToString();
	char GetChar() const;
	bool GetIsPositive() const;
	bool operator==(const Variable& other) const;
private:
	char _character;
	bool _isPositive;
};