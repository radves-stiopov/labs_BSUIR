#include "RPNEvaluator.h"

bool RPNEvaluator::CalculateRPN(std::string input, std::map<char, bool>& varValues) {
	std::stack<Token> stack;

	for (int i = 0; i < input.size(); i++) {
		if (operations.find(input[i]) != std::string::npos) {

			if (input[i] != '!') {
				Token second = stack.top();
				stack.pop();
				Token first = stack.top();
				stack.pop();
				stack.push(operation(first.getBool(), second.getBool(), input[i]));
			}
			else {
				Token variable = stack.top();
				stack.pop();
				stack.push(!variable.getBool());
			}
		}
		else {
			stack.emplace(input[i], varValues);
		}
	}
	Token finalResult = stack.top();
	return finalResult.getBool();
}

bool RPNEvaluator::operation(bool first, bool second, char operation) {
	switch (operation) {
	case '|':
		return first || second;
	case '&':
		return first && second;
	case '~':
		return first == second;
	case '>':
		return second || (!first);
	default:
		return false;
	}
}