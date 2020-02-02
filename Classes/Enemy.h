#pragma once
#include <string>
#include "SpriteBase.h"
class Rocket;

class Enemy : public SpriteBase
{
protected:
	float m_fullHealth;
	float m_health;
	int m_enemyType;
public:
	Enemy(float health, float width, float height, std::string path);
	bool isDead() { return m_health <= 0; }
	virtual void getHit(Rocket* pRocket) = 0;
	int enemyType() { return m_enemyType; }
};

