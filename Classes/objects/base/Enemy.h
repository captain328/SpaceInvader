#pragma once
#include <string>
#include "SpriteBase.h"
class Rocket;

class EnemyShip : public SpriteBase
{
protected:
	float m_fullHealth;
	float m_health;
	int m_enemyType;
	int m_scorePoint;
public:
	EnemyShip(float health, float width, float height, std::string path, int scorePoint);
	bool isDead() { return m_health <= 0; }
	virtual void getHit(Rocket* pRocket) = 0;
	int enemyType() { return m_enemyType; }
	int scorePoint() { return m_scorePoint; }
};

