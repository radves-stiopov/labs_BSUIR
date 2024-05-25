#pragma once
#include <set>
#include <vector>
#include <string>
#include <iostream>
#include "RPNFormer.h"
#include "RPNEvaluator.h"

class Table {
public:
	Table(std::set<char>& vars) {
		_table = generateBooleanVectors(vars.size(), true);
	}
	Table(std::string input);

	std::string DecimalFormConjunction() const;
	std::string DecimalFormDisjunction() const;
	std::string SDNF() const;
	std::string SKNF() const;
	std::string IndexForm() const;
	void print();
private:
	char getVarByIndex(int index) const;

	std::vector<std::vector<bool>> generateBooleanVectors(int length, bool isEmptyResult);
	std::vector<std::vector<bool>> _table;
	std::set<char> vars;
};