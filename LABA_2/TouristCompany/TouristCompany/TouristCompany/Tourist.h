#pragma once
#include <string>

class Tourist {
public:
	Tourist(std::string name, std::string phoneNumber, int age);
	std::string GetName();
	int GetAge();
	std::string GetPhoneNumber();
	void IncrementAge();
	void ChangePhoneNumber(std::string newNumber);
private:
	std::string name;
	int age;
	std::string phoneNumber;
};