#pragma once
#include <string>
#include <stack>
#include <set>

class RPNFormer {
public:
	RPNFormer(std::string input);

	std::string GetResult() {
		return RPN;
	}

	std::set<char> GetVars() {
		return vars;
	}

	std::set<char> vars;

private:
	int getOperationPriority(char operation);
	std::string RPN;
	std::string operations = "()&|!>~";
};