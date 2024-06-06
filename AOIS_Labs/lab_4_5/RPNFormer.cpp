#include "RPNFormer.h"

RPNFormer::RPNFormer(std::string input) {
	RPN = "";


	std::stack<char> stack;
	for (int i = 0; i < input.size(); i++) {

		if (input[i] == ' ' || input[i] == '-')
			continue;

		if (operations.find(input[i]) != std::string::npos) {
			if (input[i] == '(') {
				stack.push(input[i]);
			}
			else {
				while (!stack.empty() &&
					getOperationPriority(input[i]) <= getOperationPriority(stack.top())) {
					RPN += stack.top();
					stack.pop();
				}
				if (input[i] != ')') {
					stack.push(input[i]);
				}
				else {
					stack.pop();
				}
			}
		}
		else {
			vars.insert(input[i]);
			RPN += input[i];
		}
	}
	while (!stack.empty()) {
		char excess_char = stack.top();
		if (operations.find(excess_char) == std::string::npos) {
			vars.insert(excess_char);
		}
		RPN += excess_char;
		stack.pop();
	}
}

int RPNFormer::getOperationPriority(char operation) {
	if (operation == ')' || operation == '~' || operation == '>')
		return 0;
	else if (operation == '(')
		return -1;
	else if (operation == '|')
		return 1;
	else if (operation == '&')
		return 2;
	else if (operation == '!')
		return 3;
	else
		return -2;
}