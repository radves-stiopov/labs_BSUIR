#pragma once
#include <map>
#include <stack>
#include <string>

class Token {
public:
	Token(char var, std::map<char, bool>& var_values) {
		_var = var;
		_isVar = true;
		_value = var_values[var];
	}
	Token(bool value) {
		_isVar = false;
		_var = '\0';
		_value = value;
	}
	bool getBool() {
		return _value;
	}
private:
	bool _isVar;
	char _var;
	bool _value;
};

class RPNEvaluator {
public:
	bool CalculateRPN(std::string input, std::map<char, bool>& varValues);
private:
	bool operation(bool first, bool second, char operation);
	std::string operations = "()&|!>~";
};