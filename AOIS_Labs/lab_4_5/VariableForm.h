#pragma once
#include "Variable.h"
#include <vector>


class VariableForm {
public:
	VariableForm(bool isSKNF);
	VariableForm(bool isSKFN, std::string& str);
	void Add(const std::vector<Variable>& variable);
	bool GetGlued();
	bool Includes(const VariableForm& other) const;
	std::string ToString();
	static VariableForm ParseStr(std::string, bool isSKNF);
	std::vector<std::vector<Variable>> variables;
	bool isSKNF;
};