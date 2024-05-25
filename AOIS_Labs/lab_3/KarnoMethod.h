#pragma once
#include "Table.h"
#include "VariableForm.h"


class Check {
public:
	Check(bool bool_value) {
		was_included = false;
		this->bool_value = bool_value;
	}
	std::vector<bool>& GetPositivity() {
		return var_pos;
	}
	std::vector<char>& GetNames() {
		return var_name;
	}
	bool WasIncluded() {
		return was_included;
	}
	void Include() {
		was_included = true;
	}
	bool BoolValue() {
		return bool_value;
	}
	void AddVar(char name, bool pos) {
		var_name.push_back(name);
		var_pos.push_back(pos);
	}
	void SetValue(bool value) {
		bool_value = value;
	}
	int Size() {
		return var_name.size();
	}
private:
	bool was_included;
	bool bool_value;
	std::vector<char> var_name;
	std::vector<bool> var_pos;
};


class KarnoMethod {
public:
	KarnoMethod(const Table& table, bool is_SKNF);
	VariableForm GetMinimized();
	bool isValidMethod;
private:
	void makeTable1(const Table& table);
	void makeTable2(const Table& table);
	void makeTable3(const Table& table);
	void markIncluded(int _x, int _y, std::pair<int, int> area);
	bool locatedArea(int _x, int _y, std::pair<int, int> area);
	int getDoubleIndex(int firstNum, int secondNum);
	
	std::vector<Variable> getValidVariables(std::tuple<int, int, int, int>);
	void print();
	bool is_SKNF;
	std::vector<std::vector<Check>> _table;
};