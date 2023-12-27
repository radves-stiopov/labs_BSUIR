#pragma once
#include <string>

class Car {
public:
	Car(std::string brand, std::string model, int enginePower, float engineSize, int year);
	std::string GetBrand() const;
	std::string GetModel() const;
	int GetEnginePower() const;
	float GetEngineSize() const;
	int GetYear() const;
private:
	std::string brand;
	std::string model;
	int year;
	int enginePower;
	float engineSize;
};