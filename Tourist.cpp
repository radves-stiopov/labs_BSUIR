#include "Tourist.h"

Tourist::Tourist(std::string name, std::string phoneNumber, int age) : name(name), phoneNumber(phoneNumber), age(age) { }

std::string Tourist::GetName() {
	return name;
}

int Tourist::GetAge() {
	return age;
}

std::string Tourist::GetPhoneNumber() {
	return phoneNumber;
}

void Tourist::IncrementAge() {
	age++;
}

void Tourist::ChangePhoneNumber(std::string newNumber) {
	phoneNumber = newNumber;
}