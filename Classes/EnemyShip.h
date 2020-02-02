#pragma once
#include "SpriteBase.h"
#include <string>

class Rocket;

class EnemyShip :
	public SpriteBase
{
private:
	float m_fullHealth;
	float m_health;
	std::string m_normalImage;
	std::string m_hurtImage;
public:
	EnemyShip(float health, float width, float height, std::string path);
	void getHit(Rocket* pRocket);
	void reset();
	bool isDead() { return m_health <= 0; }
};
