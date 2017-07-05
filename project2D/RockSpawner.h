#pragma once
#include "Rock.h"

class RockSpawner {
public:
	RockSpawner() {}
	~RockSpawner() {}

	Rock* getRandomSizedRock(int _x1, int _x2, int _y1, int _y2) {
		return new Rock(RockSize(rand() % 3), (rand() % (_x2 - _x1)) + _x1, (rand() % (_y2 - _y1)) + _y1);
	}

	Rock* getSmallRock(int _x1, int _x2, int _y1, int _y2) {
		return new Rock(RockSize::Small, (rand() % (_x2 - _x1)) + _x1, (rand() % (_y2 - _y1)) + _y1);
	}

	Rock* getMediumRock(int _x1, int _x2, int _y1, int _y2) {
		return new Rock(RockSize::Medium, (rand() % (_x2 - _x1)) + _x1, (rand() % (_y2 - _y1)) + _y1);
	}

	Rock* getLargeRock(int _x1, int _x2, int _y1, int _y2) {
		return new Rock(RockSize::Large, (rand() % (_x2 - _x1)) + _x1, (rand() % (_y2 - _y1)) + _y1);
	}
};