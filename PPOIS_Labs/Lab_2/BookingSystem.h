#pragma once
#include "Tour.h"
#include <vector>

class BookingSystem {
public:
	void AddTour(std::string place, std::string date);
	void RemoveTour(std::string place);
	Tour& GetTour(std::string place);
private:
	std::vector<Tour> tours;
};