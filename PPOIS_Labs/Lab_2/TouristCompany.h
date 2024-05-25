#pragma once
#include <vector>
#include "TransportationSystem.h"
#include "WeatherSystem.h"
#include "BookingSystem.h"
#include "ReviewSystem.h"
#include "TourGuide.h"
#include "Tourist.h"
#include "PromotionManager.h"

class TouristCompany {
public:
	TouristCompany(std::string name);

	void AddCar(std::string brand, std::string model, int enginePower, float engineSize, int year);
	Car& GetCarByModel(std::string carName);
	Car& GetCarByPower(int enginePower);

	void ChangeCurrentStatus(std::string currentStatus);
	void ChangeTemperature(int temperature);
	std::string GetCurrentStatus();
	int GetTemperature();

	void AddPromotionManger(std::string name, int age, std::string phonoNumber);
	void ChangeManagerPhoneNumber(std::string number);
	void ChangeManagerName(std::string number);
	std::string GetManagerName();
	std::string GetManagerPhoneNumber();
	int GetManagerAge();

	void AddTour(std::string place, std::string date);
	void RemoveTour(std::string place);
	Tour& GetTour(std::string place);

	void AddTourGuide(std::string name, int age);
	TourGuide& GetTourGuide(std::string name);

	void AddTourist(std::string name, std::string phoneNumber, int age);
	Tourist& GetTourist(std::string name);

	void AddReview(int stars);
	float GetAvgRevies();
private:
	std::string companyName;
	TransportationSystem* transportationSystem;
	WeatherSystem* weatherSystem;
	BookingSystem* bookingSystem;
	std::vector<TourGuide> tourGuides;
	std::vector<Tourist> tourists;
	PromotionManager* promotionManager;
	ReviewSystem* reviewSystem;
};