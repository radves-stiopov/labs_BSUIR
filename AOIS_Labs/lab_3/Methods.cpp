#include "Methods.h"
#include "FirstStep.h"
#include "TableMethod.h"
#include "ChislMethod.h"
#include "KarnoMethod.h"

std::string MinimizeSKNFChisl(std::string input) {
	Table t(input);
	std::string tableRes = t.SKNF();
	VariableForm fullForm = VariableForm::ParseStr(tableRes, true);
	FirstStep first(fullForm, true);
	VariableForm form = first.formResult;

	ChislMethod method(form);
	VariableForm minForm = method.result;
	std::cout << std::endl;
	return minForm.ToString();
}

std::string MinimizeSDNFChisl(std::string input) {
	Table t(input);
	std::string tableRes = t.SDNF();
	VariableForm fullForm = VariableForm::ParseStr(tableRes, false);
	FirstStep first(fullForm, false);
	VariableForm form = first.formResult;

	ChislMethod method(form);
	VariableForm minForm = method.result;
	std::cout << std::endl;
	return minForm.ToString();
}

std::string MinimizeSKNFTable(std::string input) {
	Table t(input);
	std::string tableRes = t.SKNF();
	VariableForm fullForm = VariableForm::ParseStr(tableRes, true);
	FirstStep first(fullForm, true);
	VariableForm form = first.formResult;

	TableMethod method(fullForm, form);
	VariableForm minForm = method.result;
	std::cout << std::endl;
	return minForm.ToString();
}

std::string MinimizeSDNFTable(std::string input) {
	Table t(input);
	std::string tableRes = t.SDNF();
	VariableForm fullForm = VariableForm::ParseStr(tableRes, false);
	FirstStep first(fullForm, false);
	VariableForm form = first.formResult;

	TableMethod method(fullForm, form);

	VariableForm minForm = method.result;
	std::cout << std::endl;
	return minForm.ToString();
}

std::string MinimizeSKNFKarno(std::string input) {
	Table t(input);
	KarnoMethod km(t, true);
	std::cout << std::endl;
	return km.GetMinimized().ToString();
}

std::string MinimizeSDNFKarno(std::string input) {
	Table t(input);
	KarnoMethod km(t, false);
	std::cout << std::endl;
	return km.GetMinimized().ToString();
}