#pragma once
#include <string>

class PromotionManager {
public:
	PromotionManager(std::string name, int age, std::string contactNumber);
	void IncrementAge();
	void ChangeName(std::string name);
	void ChangeContactNumber(std::string number);
	std::string GetName();
	int GetAge();
	std::string GetContactNumber();
private:
	std::string name;
	std::string contactNumber;
	int age;
};