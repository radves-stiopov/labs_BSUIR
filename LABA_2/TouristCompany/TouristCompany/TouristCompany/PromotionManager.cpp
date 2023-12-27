#include "PromotionManager.h"
#include <string>

PromotionManager::PromotionManager(std::string name, int age, std::string contactNumber) : name(name), age(age), contactNumber(contactNumber) { }

void PromotionManager::IncrementAge() {
	age++;
}

void PromotionManager::ChangeName(std::string name) {
	this->name = name;
}

void PromotionManager::ChangeContactNumber(std::string number) {
	contactNumber = number;
}

std::string PromotionManager::GetName() {
	return name;
}

int PromotionManager::GetAge() {
	return age;
}

std::string PromotionManager::GetContactNumber() {
	return contactNumber;
}