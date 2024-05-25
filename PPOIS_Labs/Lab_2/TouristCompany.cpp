#include "TouristCompany.h"
#include "PromotionManager.h"

TouristCompany::TouristCompany(std::string name) : companyName(name) { 
	transportationSystem = new TransportationSystem();
	weatherSystem = new WeatherSystem();
	bookingSystem = new BookingSystem();
	promotionManager = nullptr;
	reviewSystem = new ReviewSystem();
}

void TouristCompany::AddCar(std::string brand, std::string model, int enginePower, float engineSize, int year) {
	transportationSystem->AddCar(brand, model, enginePower, engineSize, year);
}

Car& TouristCompany::GetCarByModel(std::string carName) {
	return transportationSystem->GetCarByModel(carName);
}

Car& TouristCompany::GetCarByPower(int enginePower) {
	return transportationSystem->GetCarByPower(enginePower);
}

void TouristCompany::ChangeCurrentStatus(std::string currentStatus) {
	weatherSystem->ChangeCurrentStatus(currentStatus);
}

void TouristCompany::ChangeTemperature(int temperature) {
	weatherSystem->ChangeTemperature(temperature);
}

std::string TouristCompany::GetCurrentStatus() {
	return weatherSystem->GetCurrentStatus();
}

int TouristCompany::GetTemperature() {
	return weatherSystem->GetTemperature();
}

void TouristCompany::AddPromotionManger(std::string name, int age, std::string contactNumber) {
	if (promotionManager != nullptr)
		delete promotionManager;
	promotionManager = new PromotionManager(name, age, contactNumber);
}

void TouristCompany::ChangeManagerPhoneNumber(std::string number) {
	if (promotionManager == nullptr)
		return;
	promotionManager->ChangeContactNumber(number);
}

void TouristCompany::ChangeManagerName(std::string name) {
	if (promotionManager == nullptr)
		return;
	promotionManager->ChangeName(name);
}

std::string TouristCompany::GetManagerName() {
	if (promotionManager == nullptr)
		return "";
	return promotionManager->GetName();
}

std::string TouristCompany::GetManagerPhoneNumber() {
	if (promotionManager == nullptr)
		return "";
	return promotionManager->GetContactNumber();
}

int TouristCompany::GetManagerAge() {
	if (promotionManager == nullptr)
		return 0;
	return promotionManager->GetAge();
}

void TouristCompany::AddTour(std::string place, std::string date) {
	bookingSystem->AddTour(place, date);
}

void TouristCompany::RemoveTour(std::string place) {
	bookingSystem->RemoveTour(place);
}

Tour& TouristCompany::GetTour(std::string place) {
	return bookingSystem->GetTour(place);
}

void TouristCompany::AddTourGuide(std::string name, int age) {
	tourGuides.emplace_back(name, age);
}

TourGuide& TouristCompany::GetTourGuide(std::string name) {
	auto it = find_if(tourGuides.begin(), tourGuides.end(), [&name](TourGuide& guide) { return guide.GetName() == name; });
	return *it;
}

void TouristCompany::AddTourist(std::string name, std::string phoneNumber, int age) {
	tourists.emplace_back(name, phoneNumber, age);
}

Tourist& TouristCompany::GetTourist(std::string name) {
	auto it = find_if(tourists.begin(), tourists.end(), [&name](Tourist& tour) { return tour.GetName() == name; });
	return *it;
}

void TouristCompany::AddReview(int stars) {
	reviewSystem->AddRating(stars);
}

float TouristCompany::GetAvgRevies() {
	return reviewSystem->GetAverageRating();
}