#pragma once
#include <string>

class Tour {
public:
	Tour(std::string place, std::string date);
	std::string GetDate() const;
	std::string GetPlace() const;
private:
	std::string date;
	std::string place;
};