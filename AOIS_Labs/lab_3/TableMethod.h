#pragma once
#include <vector>
#include "VariableForm.h"

class TableMethod {
public:
	TableMethod(const VariableForm& fullForm, const VariableForm& shortForm);
	VariableForm result;
private:
	std::vector<std::vector<bool>> _is_included;
	std::vector<VariableForm> full;
	std::vector<VariableForm> shortened;
};