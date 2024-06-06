#include "Variable.h"
#include <iostream>

Variable::Variable(char character, bool isPositive) {
	_character = character;
	_isPositive = isPositive;
}

bool Variable::Equals(const Variable& other) const {
	return _character == other._character && _isPositive == other._isPositive;
}

std::string Variable::ToString() {
	return _isPositive ? std::string(1, _character) : "!" + std::string(1, _character);
}

char Variable::GetChar() const {
	return _character;
}

bool Variable::GetIsPositive() const {
	return _isPositive;
}

bool Variable::operator==(const Variable& other) const {
	return Equals(other);
}