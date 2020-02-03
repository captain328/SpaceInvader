#pragma once
#include "SpriteBase.h"
#include "Enemy.h"
#include <string>

class Rocket;

class HeavyEnemyShip : public Enemy
{
private:
	std::string m_normalImage;
	std::string m_hurtImage;
public:
	HeavyEnemyShip(float health, float width, float height, std::string path);
	virtual void getHit(Rocket* pRocket);
	void reset();
	
};
