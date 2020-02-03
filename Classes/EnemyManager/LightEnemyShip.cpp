#include "LightEnemyShip.h"
#include "Rocket.h"
#include "Config.h"

LightEnemyShip::LightEnemyShip(float health, float width, float height, std::string path)
	: Enemy(health, width, height, path)
{
	setTag(TAG_ENEMY_SHIP);
	m_enemyType = ENEMY_SHIP_HEAVY;
	// EnemyShip has to be displayed as flipped
	setFlippedY(true);
}

void LightEnemyShip::reset()
{
	this->m_health = m_fullHealth;
}

void LightEnemyShip::getHit(Rocket*)
{
	// light enemy ship gets destroy instantly it is hit
	m_health = 0;
}