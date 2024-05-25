#include "TableMethod.h"
#include <iostream>

TableMethod::TableMethod(const VariableForm& fullForm, const VariableForm& shortForm) : result(fullForm.isSKNF) {
	for (auto& brackets : fullForm.variables) {
		VariableForm form(fullForm.isSKNF);
		form.Add(brackets);
		full.push_back(form);
	}

	for (auto& brackets : shortForm.variables) {
		VariableForm form(shortForm.isSKNF);
		form.Add(brackets);
		shortened.push_back(form);
	}

	_is_included.resize(shortened.size(), std::vector<bool>(fullForm.variables.size()));

	for (int i = 0; i < shortForm.variables.size(); i++) {
		VariableForm checkShort(shortForm.isSKNF);
		checkShort.Add(shortForm.variables[i]);
		for (int j = 0; j < fullForm.variables.size(); j++) {
			
			VariableForm checkFull(fullForm.isSKNF);
			checkFull.Add(fullForm.variables[j]);

			if (checkFull.Includes(checkShort)) {
				_is_included[i][j] = true;
			}
		}
	}
	std::cout << "Table method" << std::endl;
	for (int x = 0; x < _is_included.size(); x++) {
		for (int y = 0; y < _is_included[x].size(); y++) {
			std::cout << _is_included[x][y] << " ";
		}
		std::cout << std::endl;
	}
	for (int i = 0; i < _is_included.size(); i++) {
		bool is_remove = true;
		for (int j = 0; j < _is_included[i].size(); j++) {
			bool are_false = true;
			if (_is_included[i][j] == false)
				continue;

			for (int k = 0; k < _is_included.size(); k++) {
				if (k == i)
					continue;
				if (_is_included[k][j]) {
					are_false = false;
					break;
				}

			}
			
			if (are_false) {
				is_remove = false;
			}
		}
		if (is_remove) {
			shortened.erase(shortened.begin() + i);
			_is_included.erase(_is_included.begin() + i);
			i--;
		}
	}

	for (auto& form : shortened) {
		result.Add(form.variables[0]);
	}

}