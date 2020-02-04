#pragma once
#include "SpriteBase.h"

class Rocket;

class HeroShip :
	public SpriteBase
{
public:
	HeroShip();
	Rocket* fire();
};
