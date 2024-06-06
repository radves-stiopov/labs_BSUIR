#include "Table.h"

Table::Table(std::string input) {
	RPNFormer former(input);

	std::string rpn = former.GetResult();
	vars = former.GetVars();

	RPNEvaluator evaluator;
	std::map<char, bool> varValues;
	std::vector<std::vector<bool>> tableWithoutResult = generateBooleanVectors(vars.size(), false);

	for (int i = 0; i < tableWithoutResult.size(); i++) {
		std::vector<bool> row(vars.size());
		std::copy(tableWithoutResult[i].begin(), tableWithoutResult[i].end(), row.begin());
		auto vars_it = vars.begin();
		for (int j = 0; j < row.size(); j++) {
			varValues[*vars_it] = row[j];
			vars_it++;
		}

		bool result = evaluator.CalculateRPN(rpn, varValues);
		row.push_back(result);
		_table.push_back(row);
	}
}

std::string Table::DecimalFormConjunction() const {
	std::vector<int> form;
	for (int i = 0; i < _table.size(); i++) {
		bool result = _table[i][_table[i].size() - 1];
		if (result == false) {
			form.push_back(i);
		}
	}

	std::string output = "(";
	bool first = true;
	for (auto& number : form) {
		if (!first) {
			output += ", ";
		}

		output += std::to_string(number);
		first = false;
	}

	output += ") and";
	return output;
}

std::string Table::DecimalFormDisjunction() const {
	std::vector<int> form;
	for (int i = 0; i < _table.size(); i++) {
		bool result = _table[i][_table[i].size() - 1];
		if (result) {
			form.push_back(i);
		}
	}

	std::string output = "(";
	bool first = true;
	for (auto& number : form) {
		if (!first) {
			output += ", ";
		}

		output += std::to_string(number);
		first = false;
	}

	output += ") or";
	return output;
}

std::string Table::SDNF() const {
	std::string output = "";
	for (int i = 0; i < _table.size(); i++) {
		bool result = _table[i][_table[i].size() - 1];
		if (result == true) {
			output += "(";
			for (int j = 0; j < _table[i].size() - 1; j++) {
				if (!_table[i][j]) {
					output += std::string("!") + getVarByIndex(j);
				}
				else {
					output += getVarByIndex(j);
				}
				output += "&";
			}
			output.pop_back();
			output += ") | ";
		}
	}
	output.pop_back();
	output.pop_back();
	return output;
}

std::string Table::SKNF() const {
	std::string output = "";
	for (int i = 0; i < _table.size(); i++) {
		bool result = _table[i][_table[i].size() - 1];
		if (result == false) {
			output += "(";
			for (int j = 0; j < _table[i].size() - 1; j++) {
				if (_table[i][j]) {
					output += std::string("!") + getVarByIndex(j);
				}
				else {
					output += getVarByIndex(j);
				}
				output += "|";
			}
			output.pop_back();
			output += ") & ";
		}
	}
	output.pop_back();
	output.pop_back();
	return output;
}

std::string Table::IndexForm() const {
	unsigned long long indexForm = 0;
	std::string binary = "";
	for (int i = 0; i < _table.size(); i++) {
		bool result = _table[i][_table[i].size() - 1];
		if (result == true) {
			indexForm |= 1;
			binary += "1";
		}
		else {
			binary += "0";
		}
		if (i != _table.size() - 1)
			indexForm <<= 1;
	}
	return std::to_string(indexForm) + ": " + binary;
}

char Table::getVarByIndex(int index) const {
	auto vars_it = vars.begin();
	for (int i = 0; i < index; i++) {
		vars_it++;
	}
	return *vars_it;
}

void Table::changeResults(std::vector<bool> results) {
	if (results.size() != _table.size()) {
		std::cout << "Error: table" << std::endl;
		return;
	}

	for (int i = 0; i < results.size(); i++) {
		_table[i][_table[i].size() - 1] = results[i];
	}
}

std::vector<std::vector<bool>> Table::generateBooleanVectors(int length, bool isEmptyResult) {
	std::vector<std::vector<bool>> result;
	int total = 1 << length;

	for (int i = 0; i < total; ++i) {
		std::vector<bool> vec(length);
		for (int j = 0; j < length; ++j) {
			vec[length - 1 - j] = (i >> j) & 1;
		}
		if (isEmptyResult)
			vec.push_back(false);
		result.push_back(vec);
	}

	return result;
}

void Table::print() {
	for (int i = 0; i < _table.size(); i++) {
		for (int j = 0; j < _table[i].size(); j++) {
			std::cout << _table[i][j] << " ";
		}
		std::cout << std::endl;
	}
}