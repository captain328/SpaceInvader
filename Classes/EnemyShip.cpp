#include "EnemyShip.h"
#include "Rocket.h"
#include "Config.h"

EnemyShip::EnemyShip(float health, float width, float height, std::string path)
	: SpriteBase(width, height, path)
{
	m_health = health;
	SetSpriteKind(TAG_ENEMY_SHIP);
	// EnemyShip has to be displayed as flipped
	setFlippedY(true);
}

void EnemyShip::getHit(Rocket* pRocket)
{
	this->m_health -= pRocket->power();
/*	if (this->m_health >= 0) {
		this.createWith
	}*/
}
