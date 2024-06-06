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
	return minForm.ToString();
}

std::string MinimizeSKNFKarno(std::string input) {
	Table t(input);
	KarnoMethod km(t, true);
	return km.GetMinimized().ToString();
}

std::string MinimizeSDNFKarno(std::string input) {
	Table t(input);
	KarnoMethod km(t, false);
	return km.GetMinimized().ToString();
}

void PrintMinus() {
	std::set<char> vars;
	vars.insert('a');
	vars.insert('b');
	vars.insert('p');
	Table td(vars);
	std::vector<bool> vd = { 0, 1, 1, 0, 1, 0, 0, 1 };
	td.changeResults(vd);
	Table tv(vars);
	std::vector<bool> vv = { 0, 1, 1, 1, 0, 0, 0, 1 };
	tv.changeResults(vv);
	
	KarnoMethod kmd(td, false);
	KarnoMethod kmt(tv, false);
	std::cout << "Minimized" << std::endl;
	std::cout << "d: " << kmd.GetMinimized().ToString() << std::endl;
	std::cout << "v: " << kmt.GetMinimized().ToString() << std::endl;
	std::cout << std::endl;
}

void Print2() {
	std::set<char> vars;
	vars.insert('0');
	vars.insert('1');
	vars.insert('2');
	vars.insert('3');
	Table t0(vars);
	std::vector<bool> v0 = { 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0 };
	t0.changeResults(v0);
	Table t1(vars);
	std::vector<bool> v1 = { 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	t1.changeResults(v1);
	Table t2(vars);
	std::vector<bool> v2 = { 1, 1, 0, 0, 1, 1, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0 };
	t2.changeResults(v2);
	Table t3(vars);
	std::vector<bool> v3 = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0 };
	t3.changeResults(v3);

	KarnoMethod km0(t0, false);
	KarnoMethod km1(t1, false);
	KarnoMethod km2(t2, false);
	KarnoMethod km3(t3, false);
	std::cout << "Minimized" << std::endl;
	std::cout << "x0: " << km0.GetMinimized().ToString() << std::endl;
	std::cout << "x1: " << km1.GetMinimized().ToString() << std::endl;
	std::cout << "x2: " << km2.GetMinimized().ToString() << std::endl;
	std::cout << "x3: " << km3.GetMinimized().ToString() << std::endl;
	std::cout << std::endl;
}

void Triggers() {
	std::set<char> vars;
	vars.insert('v');
	vars.insert('1');
	vars.insert('2');
	vars.insert('3');
	vars.insert('4');
	
	Table t1(vars);
	std::vector<bool> h1 = { 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1 };
	t1.changeResults(h1);
	Table t2(vars);
	std::vector<bool> h2 = { 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0, 0 };
	t2.changeResults(h2);
	Table t3(vars);
	std::vector<bool> h3 = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0 };
	t3.changeResults(h3);
	Table t4(vars);
	std::vector<bool> h4 = { 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	t4.changeResults(h4);

	
	std::string km1 = MinimizeSDNFChisl(t1.SDNF());
	std::string km2 = MinimizeSDNFChisl(t2.SDNF());
	std::string km3 = MinimizeSDNFChisl(t3.SDNF());
	std::string km4 = MinimizeSDNFChisl(t4.SDNF());
	std::cout << "Minimized" << std::endl;
	std::cout << "h1: " << km1 << std::endl;
	std::cout << "h2: " << km2 << std::endl;
	std::cout << "h3: " << km3 << std::endl;
	std::cout << "h4: " << km4 << std::endl;
}