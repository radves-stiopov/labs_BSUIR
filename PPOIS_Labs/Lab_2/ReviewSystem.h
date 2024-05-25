#pragma once

class ReviewSystem {
public:
	void AddRating(int stars);
	float GetAverageRating();
private:
	int totalStars;
	int count;
};