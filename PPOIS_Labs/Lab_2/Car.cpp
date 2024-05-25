#include "Car.h"

Car::Car(std::string brand, std::string model, int enginePower, float engineSize, int year) : brand(brand), model(model), enginePower(enginePower), engineSize(engineSize), year(year) {

}

std::string Car::GetBrand() const {
	return brand;
}

std::string Car::GetModel() const {
	return model;
}

int Car::GetEnginePower() const {
	return enginePower;
}

float Car::GetEngineSize() const {
	return engineSize;
}
int Car::GetYear() const {
	return year;
}