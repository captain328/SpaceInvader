#include "Enemy.h"
#include "SpriteBase.h"
#include "Config.h"

EnemyShip::EnemyShip(float health, float width, float height, std::string path)
	: SpriteBase(width, height, path)
{
	m_health = health;
	m_fullHealth = m_health;
	setTag(TAG_ENEMY_SHIP);
	setFlippedY(true);
}
