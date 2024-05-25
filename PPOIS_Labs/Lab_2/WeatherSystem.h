#pragma once
#include <string>

class WeatherSystem {
public:
	WeatherSystem();
	void ChangeCurrentStatus(std::string currentStatus);
	void ChangeTemperature(int temperature);
	std::string GetCurrentStatus();
	int GetTemperature();
private:
	std::string currentStatus;
	int temperature;
};