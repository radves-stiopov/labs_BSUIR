#pragma once
#include "Car.h"
#include <string>
#include <vector>

class TransportationSystem {
public:
	void AddCar(std::string brand, std::string model, int enginePower, float engineSize, int year);
	Car& GetCarByModel(std::string carName);
	Car& GetCarByPower(int enginePower);
private:
	std::vector<Car> cars;
};