#pragma once
#include "SpriteObject.h"

enum RockSize { Small, Medium, Large };

class Rock : public SpriteObject
{
public:
	Rock(RockSize s, float x, float y);
	~Rock() {}

	void destroy();

	static std::string rockTextures[3];
};