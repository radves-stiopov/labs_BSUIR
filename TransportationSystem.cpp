#include "TransportationSystem.h"
#include <algorithm>

void TransportationSystem::AddCar(std::string brand, std::string model, int enginePower, float engineSize, int year) {
	cars.emplace_back(brand, model, enginePower, engineSize, year);
}

Car& TransportationSystem::GetCarByModel(std::string carName) {
	auto it = find_if(cars.begin(), cars.end(), [&carName](const Car& car) { return car.GetModel() == carName; });
	return *it;
}

Car& TransportationSystem::GetCarByPower(int enginePower) {
	auto it = find_if(cars.begin(), cars.end(), [&enginePower](const Car& car) { return car.GetEnginePower() == enginePower; });
	return *it;
}
