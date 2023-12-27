#include "TourGuide.h"
#include <string>

TourGuide::TourGuide(std::string name, int age) : name(name), age(age) {

}

void TourGuide::IncrementAge() {
	age++;
}

void TourGuide::ChangeName(std::string name) {
	this->name = name;
}

std::string TourGuide::GetName() {
	return name;
}

int TourGuide::GetAge() {
	return age;
}