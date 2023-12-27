#pragma once
#include <string>

class TourGuide {
public:
	TourGuide(std::string name, int age);
	void IncrementAge();
	void ChangeName(std::string name);
	std::string GetName();
	int GetAge();
private:
	std::string name;
	int age;
};