#include "WeatherSystem.h" 

WeatherSystem::WeatherSystem() : currentStatus("Normal"), temperature(20) { }

std::string WeatherSystem::GetCurrentStatus() {
	return currentStatus;
}

int WeatherSystem::GetTemperature() {
	return temperature;
}

void WeatherSystem::ChangeCurrentStatus(std::string currentStatus) {
	this->currentStatus = currentStatus;
}
void WeatherSystem::ChangeTemperature(int temperature) {
	this->temperature = temperature;
}