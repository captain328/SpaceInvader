#pragma once
#include "SpriteBase.h"

class Rocket;

class SpaceShip :
	public SpriteBase
{
public:
	SpaceShip(float width, float height, std::string path);
	Rocket* fire();
};
