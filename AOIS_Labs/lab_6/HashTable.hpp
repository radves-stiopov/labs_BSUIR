#include <string>
#include <vector>

class Cell {
public:
	void Update(std::string key, std::string value) {
		is_ocupied = true;
		was_deleted = false;
		this->key = key;
		val = value;
	}

	void Delete() {
		is_ocupied = false;
		was_deleted = true;
		key = "";
	}

	bool GetIsOcupied() {
		return is_ocupied;
	}

	bool GetWasDeleted() {
		return was_deleted;
	}

	std::string GetKey() {
		return key;
	}

	std::string GetVal() {
		return val;
	}
private:
	bool is_ocupied = false;
	bool was_deleted = false;
	std::string key = "";
	std::string val = "";
};

class HashTable {
public:
	HashTable() {
		table.resize(tableSize);
	}

	HashTable(int size) {
		tableSize = size;
		table.resize(tableSize);
	}

	void Insert(std::string key, std::string val);

	std::string Get(std::string key);

	void Update(std::string key, std::string newVal);

	void Delete(std::string key);
private:
	void resize(size_t newSize);

	size_t HashFunction(std::string key);
	size_t tableSize = 10;
	size_t stored = 0;
	int step = 3;
	std::vector<Cell> table;
};