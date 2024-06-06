#include "KarnoMethod.h"

KarnoMethod::KarnoMethod(const Table& table, bool is_SKNF) {
	this->is_SKNF = is_SKNF;
	if (table._table[0].size() == 3) {
		makeTable1(table);
		isValidMethod = true;
	}
	else if (table._table[0].size() == 4) {
		makeTable2(table);
		isValidMethod = true;
	}
	else if (table._table[0].size() == 5) {
		makeTable3(table);
		isValidMethod = true;
	}
	else {
		isValidMethod = false;
		return;
	}
}


int KarnoMethod::getDoubleIndex(int firstNum, int secondNum) {
	if (firstNum == 0) {
		return secondNum;
	}
	else {
		if (secondNum == 0) {
			return 3;
		}
		else {
			return 2;
		}
	}
}

void KarnoMethod::makeTable1(const Table& table) {
	_table.resize(2, std::vector<Check>(2, false));
	for (int i = 0; i < table._table.size(); i++) {
		int y = table._table[i][0];
		int x = table._table[i][1];

		_table[y][x].AddVar(table.getVarByIndex(0), table._table[i][0]);
		_table[y][x].AddVar(table.getVarByIndex(1), table._table[i][1]);
		_table[y][x].SetValue(table._table[i][2]);
	}
}

void KarnoMethod::makeTable2(const Table& table) {
	_table.resize(2, std::vector<Check>(4, false));
	for (int i = 0; i < table._table.size(); i++) {
		int y = table._table[i][0];
		int x = getDoubleIndex(table._table[i][1], table._table[i][2]);

		_table[y][x].AddVar(table.getVarByIndex(0), table._table[i][0]);
		_table[y][x].AddVar(table.getVarByIndex(1), table._table[i][1]);
		_table[y][x].AddVar(table.getVarByIndex(2), table._table[i][2]);
		_table[y][x].SetValue(table._table[i][3]);
	}
}

void KarnoMethod::makeTable3(const Table& table) {
	_table.resize(4, std::vector<Check>(4, false));
	for (int i = 0; i < table._table.size(); i++) {
		int y = getDoubleIndex(table._table[i][0], table._table[i][1]);
		int x = getDoubleIndex(table._table[i][2], table._table[i][3]);

		_table[y][x].AddVar(table.getVarByIndex(0), table._table[i][0]);
		_table[y][x].AddVar(table.getVarByIndex(1), table._table[i][1]);
		_table[y][x].AddVar(table.getVarByIndex(2), table._table[i][2]);
		_table[y][x].AddVar(table.getVarByIndex(3), table._table[i][3]);
		_table[y][x].SetValue(table._table[i][4]);
	}
}

bool KarnoMethod::locatedArea(int _x, int _y, std::pair<int, int> area) {
	bool wereIncluded = true;

	for (int y = 0; y < area.second; y++) {
		for (int x = 0; x < area.first; x++) {
			int calc_y = (y + _y) % _table.size();
			int calc_x = (x + _x) % _table[0].size();
			Check& check = _table[calc_y][calc_x];

			if (check.WasIncluded() == false) {
				wereIncluded = false;
			}

			if (check.BoolValue() == is_SKNF) {
				return false;
			}
		}
	}

	return !wereIncluded;
}

std::vector<Variable> KarnoMethod::getValidVariables(std::tuple<int, int, int, int> area) {
	Check& firstCheck = _table[std::get<1>(area)][std::get<0>(area)];
	std::vector<Variable> result;
	for (int i = 0; i < firstCheck.Size(); i++) {
		char curName = firstCheck.GetNames()[i];
		bool curPos = firstCheck.GetPositivity()[i];
		bool is_add = true;
		for (int y = 0; y < std::get<3>(area); y++) {
			for (int x = 0; x < std::get<2>(area); x++) {
				int calc_y = (y + std::get<1>(area)) % _table.size();
				int calc_x = (x + std::get<0>(area)) % _table[0].size();
				Check& otherCheck = _table[calc_y][calc_x];
				char otherName = otherCheck.GetNames()[i];
				bool otherPos = otherCheck.GetPositivity()[i];
				if (curName != otherName || curPos != otherPos) {
					is_add = false;
					goto breakLoop;
				}
			}
		}
breakLoop:
		if (is_add) {
			if (is_SKNF)
				curPos = !curPos;
			result.emplace_back(curName, curPos);
		}
	}
	return result;
}

void KarnoMethod::markIncluded(int _x, int _y, std::pair<int, int> area) {
	for (int y = 0; y < area.second; y++) {
		for (int x = 0; x < area.first; x++) {
			_table[(y + _y) % _table.size()][(x + _x) % _table[0].size()].Include();
		}
	}
}

void KarnoMethod::print() {
	for (int i = 0; i < _table.size(); i++) {
		for (int j = 0; j < _table[i].size(); j++) {
			std::cout << _table[i][j].BoolValue() << " ";
		}
		std::cout << "\n";
	}
}

VariableForm KarnoMethod::GetMinimized() {
	std::vector<std::pair<int, int>> AREAS = {{
		{1, 8},	{8, 1},	{4, 4},
		{2, 4},	{4, 2},	{2, 2},	
		{1, 4},	{4, 1},	{1, 2},
		{2, 1},	{1, 1}}};
	std::vector<std::tuple<int, int, int, int>> checkAreas;
	for (int i = 0; i < AREAS.size(); i++) {

		while (AREAS[i].second > _table.size() || AREAS[i].first > _table[0].size()) {
			i++;
			if (i == AREAS.size()) {
				goto breakAreaLoop;
			}
		}


		for (int y = 0; y < _table.size(); y++) {
			for (int x = 0; x < _table[0].size(); x++) {
				if (locatedArea(x, y, AREAS[i])) {
					checkAreas.emplace_back(x, y, AREAS[i].first, AREAS[i].second);
					markIncluded(x, y, AREAS[i]);
				}
			}
		}
	}
breakAreaLoop:
	VariableForm result(is_SKNF);
	for (auto& checkArea : checkAreas) {
		result.Add(getValidVariables(checkArea));
	}
	return result;
}