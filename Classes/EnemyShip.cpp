#include "EnemyShip.h"
#include "Rocket.h"
#include "Config.h"

EnemyShip::EnemyShip(float health, float width, float height, std::string path)
	: SpriteBase(width, height, path)
{
	m_health = health;
	SetSpriteKind(TAG_ENEMY_SHIP);
	m_hurtImage = HEAVY_ENEMY_HIT_PATH;
	m_normalImage = path;
	// EnemyShip has to be displayed as flipped
	setFlippedY(true);
}

void EnemyShip::getHit(Rocket* pRocket)
{
	this->m_health -= pRocket->power();
	cocos2d::Size sz = this->getContentSize();
	if (this->m_health >= 0) {
		this->setTexture(m_hurtImage);
		this->setContentSize(sz);
	}
}

void EnemyShip::reset()
{
	this->m_health = m_fullHealth;
	cocos2d::Size sz = this->getContentSize();
	this->setTexture(m_normalImage);
	this->setContentSize(sz);
}