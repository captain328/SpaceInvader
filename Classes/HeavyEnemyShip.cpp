#include "HeavyEnemyShip.h"
#include "Rocket.h"
#include "Config.h"

HeavyEnemyShip::HeavyEnemyShip(float health, float width, float height, std::string path)
	: Enemy(health, width, height, path)
{
	setTag(TAG_ENEMY_SHIP);
	m_hurtImage = HEAVY_ENEMY_HIT_PATH;
	m_normalImage = path;
	m_enemyType = ENEMY_SHIP_HEAVY;
	// EnemyShip has to be displayed as flipped
	setFlippedY(true);
}

void HeavyEnemyShip::getHit(Rocket* pRocket)
{
	this->m_health -= pRocket->power();
	cocos2d::Size sz = this->getContentSize();
	if (this->m_health >= 0) {
		this->setTexture(m_hurtImage);
		this->setContentSize(sz);
	}
}

void HeavyEnemyShip::reset()
{
	this->m_health = m_fullHealth;
	cocos2d::Size sz = this->getContentSize();
	this->setTexture(m_normalImage);
	this->setContentSize(sz);
}
