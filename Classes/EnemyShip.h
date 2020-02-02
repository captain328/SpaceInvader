#pragma once
#include "SpriteBase.h"

class Rocket;

class EnemyShip :
	public SpriteBase
{
private:
	float m_health;
public:
	EnemyShip(float health, float width, float height, std::string path);
	void getHit(Rocket* pRocket);
	bool isDead() { return m_health <= 0; }
};
