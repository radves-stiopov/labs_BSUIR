#include "ReviewSystem.h"

void ReviewSystem::AddRating(int stars) {
	if (stars > 5)
		stars = 5;
	else if (stars < 0)
		stars = 0;

	totalStars += stars;
	count++;
}

float ReviewSystem::GetAverageRating() {
	return (float)totalStars / count;
}