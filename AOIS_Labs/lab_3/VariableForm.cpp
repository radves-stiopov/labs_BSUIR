#include "VariableForm.h"
#include <set>
#include <algorithm>
#include <iterator>
#include <iostream>

VariableForm::VariableForm(bool isSKNF) {
	this->isSKNF = isSKNF;
}

void VariableForm::Add(const std::vector<Variable>& variable) {
	variables.push_back(variable);
}

bool VariableForm::GetGlued() {
	std::vector<std::pair<int, char>> to_remove;
	for (int i = 0; i < variables.size(); i++) {
		for (int j = i + 1; j < variables.size(); j++) {
			if (variables[i].size() != variables[j].size())
				continue;
			if (variables[i].size() == 1 || variables[j].size() == 1)
				continue;
			auto compare = [](Variable& var1, Variable& var2) {
				int val1 = var1.GetChar();
				int val2 = var2.GetChar();
				if (!var1.GetIsPositive())
					val1 *= -1;
				if (!var2.GetIsPositive())
					val2 *= -1;
				return val1 < val2;
			};
			std::sort(variables[i].begin(), variables[i].end(), compare);
			std::sort(variables[j].begin(), variables[j].end(), compare);
			std::vector<Variable> sym_diff;
			
			std::set_symmetric_difference(variables[i].begin(), variables[i].end(), variables[j].begin(), variables[j].end(), std::back_inserter(sym_diff), compare);
			if (sym_diff.size() != 2)
				continue;

			if (sym_diff[0].GetChar() == sym_diff[1].GetChar()
				&& sym_diff[0].GetIsPositive() != sym_diff[1].GetIsPositive()) {
				to_remove.emplace_back(i, sym_diff[0].GetChar());
				to_remove.emplace_back(j, sym_diff[0].GetChar());
			}
		}
	}
	bool was_removed = false;
	int i = 0;
	for (auto& [ind, charValue] : to_remove) {
		i++;
		if (i % 2 == 0) {
			continue;
		}
		std::vector<Variable> newInBrackets;
		std::copy_if(variables[ind].begin(), variables[ind].end(), std::back_inserter(newInBrackets), [charValue](Variable& first) {
			return first.GetChar() != charValue;
			});

		variables.push_back(newInBrackets);

		was_removed = true;
	}

	std::sort(to_remove.begin(), to_remove.end(), [](auto& first, auto& second) {
		return first.first > second.first;
		});

	to_remove.erase(std::unique(to_remove.begin(), to_remove.end(), [](auto& first, auto& second) {
		return first.first == second.first;
		}), to_remove.end());

	for (auto& [ind, charValue] : to_remove) {
		variables.erase(variables.begin() + ind);
	}
	std::vector<int> ind_remove;
	for (int i = 0; i < variables.size(); i++) {
		for (int j = i + 1; j < variables.size(); j++) {
			bool areEqual = true;
			for (int y = 0; y < variables[i].size(); y++) {
				for (int z = 0; z < variables[j].size(); z++) {
					if (variables[i][y] != variables[j][z]) {
						areEqual = false;
						break;
					}
				}
			}
			if (areEqual) {
				ind_remove.push_back(i);
			}
		}
	}
	std::sort(ind_remove.begin(), ind_remove.end(), [](int a, int b) { return a > b; });
	ind_remove.erase(std::unique(ind_remove.begin(), ind_remove.end()), ind_remove.end());
	for (int i = 0; i <ind_remove.size(); i++) {
		variables.erase(variables.begin() + ind_remove[i]);
	}
	return was_removed;
}

bool VariableForm::Includes(const VariableForm& other) const {
	return std::all_of(other.variables[0].begin(), other.variables[0].end(),
		[&](auto& x) { 
		return std::any_of(variables[0].begin(), variables[0].end(),
			[&](auto& y) { 
				return y == x; 
			});
	});
}

std::string VariableForm::ToString() {
	std::string result = "";
	for (auto& inBrackets : variables) {
		result += '(';
		for (auto& elem : inBrackets) {
			result += elem.ToString() + (isSKNF ? '|' : '&');
		}
		result.pop_back();
		result += std::string(")") + (isSKNF ? '&' : '|');
	}
	result.pop_back();
	return result;
}


VariableForm VariableForm::ParseStr(std::string input, bool isSKNF) {
	VariableForm form(isSKNF);
	std::vector<Variable> varsInBrackets;
	bool isPositive = true;
	for (char currentChar : input) {
		if (currentChar == '!') {
			isPositive = false;
			continue;
		}
		if (currentChar == ' ' || currentChar == '(' || currentChar == '&' || currentChar == '|')
			continue;

		if (currentChar == ')') {
			form.Add(varsInBrackets);
			varsInBrackets.clear();
			continue;
		}

		varsInBrackets.emplace_back(currentChar, isPositive);
		isPositive = true;
	}
	return form;
}