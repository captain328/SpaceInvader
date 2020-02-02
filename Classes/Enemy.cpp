#include "Enemy.h"
#include "SpriteBase.h"

Enemy::Enemy(float health, float width, float height, std::string path)
	: SpriteBase(width, height, path)
{
	m_health = health;
	m_fullHealth = m_health;
}
