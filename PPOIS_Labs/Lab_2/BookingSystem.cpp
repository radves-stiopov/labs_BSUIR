#include "BookingSystem.h"
#include <algorithm>

void BookingSystem::AddTour(std::string place, std::string date) {
	tours.emplace_back(place, date);
}


void BookingSystem::RemoveTour(std::string place) {
	std::remove_if(tours.begin(), tours.end(), [&place](const Tour& tour) { return tour.GetPlace() == place; });
}

Tour& BookingSystem::GetTour(std::string place) {
	auto it = std::find_if(tours.begin(), tours.end(), [&place](const Tour& tour) {return tour.GetPlace() == place; });
	return *it;
}