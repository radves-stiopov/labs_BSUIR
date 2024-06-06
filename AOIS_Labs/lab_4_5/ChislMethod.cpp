#include "ChislMethod.h"
#include <map>
#include <algorithm>
#include <ranges>

ChislMethod::ChislMethod(VariableForm shortForm) : result(shortForm.isSKNF) {
	std::vector<int> to_remove_vec;
	for (int i = 0; i < shortForm.variables.size(); i++) {
		std::map<char, bool> bracketsVariables;
		for (int j = 0; j < shortForm.variables[i].size(); j++) {
			bracketsVariables.emplace(shortForm.variables[i][j].GetChar(), shortForm.variables[i][j].GetIsPositive());
		}
		bool to_remove = false;
		for (int j = 0; j < shortForm.variables.size(); j++) {
			if (j == i)
				continue;
			bool is_valid = false;
			for (const Variable& var : shortForm.variables[j]) {
				auto find_it = bracketsVariables.find(var.GetChar());
				if (find_it == bracketsVariables.end()) {
					is_valid = true;
					break;
				}
				else {
					if (find_it->second != var.GetIsPositive()) {
						is_valid = true;
						break;
					}
				}
			}
			if (!is_valid) {
				to_remove = true;
				break;
			}
		}
		if (to_remove) {
			shortForm.variables.erase(shortForm.variables.begin() + i);
			i--;
		}
	}
	result = shortForm;
}