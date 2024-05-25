#include <string>
#include "Tour.h"

Tour::Tour(std::string place, std::string date) : date(date), place(place) { }

std::string Tour::GetDate() const {
	return date;
}

std::string Tour::GetPlace() const {
	return place;
}