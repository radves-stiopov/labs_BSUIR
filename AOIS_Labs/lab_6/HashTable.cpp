#include "HashTable.hpp"

void HashTable::Insert(std::string key, std::string val) {
	if (key != "") {
		int position = HashFunction(key);
		int tries = 1;
		while (table[position].GetIsOcupied() == true) {
			if (table[position].GetKey() == key) {
				throw std::exception("The key is already present in the hashtable!");
			}
			position += step * tries;
			tries++;
			position %= tableSize;

		}
		stored++;
		table[position].Update(key, val);
		if (stored * 3 >= tableSize) {
			resize(tableSize * 3);
		}
	}
}

std::string HashTable::Get(std::string key) {
	if (key != "") {
		int position = HashFunction(key);

		int tries = 1;
		while (table[position].GetKey() != key) {
			if (table[position].GetIsOcupied() == false && table[position].GetWasDeleted() == false)
				throw std::exception("No such element!");


			position += step * tries;
			tries++;
			position %= tableSize;

		}

		return table[position].GetVal();
	}
}

void HashTable::Update(std::string key, std::string newVal) {
	if (key != "") {
		int position = HashFunction(key);
		int tries = 1;

		while (table[position].GetKey() != key) {
			if (table[position].GetIsOcupied() == false) {
				throw std::exception("No such element!");
			}
			position += step * tries;
			tries++;
			position %= tableSize;

		}

		table[position].Update(key, newVal);
	}
}

void HashTable::Delete(std::string key) {
	if (key != "") {
		int position = HashFunction(key);
		int tries = 1;
		while (table[position].GetKey() != key) {
			if (table[position].GetIsOcupied() == false && table[position].GetWasDeleted() == false) {
				throw std::exception("No such element!");
			}
			position += step * tries;
			tries++;
			position %= tableSize;

		}
		stored--;
		table[position].Delete();
	}
}

void HashTable::resize(size_t newSize) {
	HashTable newTable(newSize);
	for (auto& cell : table) {
		newTable.Insert(cell.GetKey(), cell.GetVal());
	}

	*this = newTable;
}

size_t HashTable::HashFunction(std::string key) {
	if (key.size() == 1) {
		return (key[0] * 17) % tableSize;
	}
	else {
		return (key[0] * key[1] * 17) % tableSize;
	}
}