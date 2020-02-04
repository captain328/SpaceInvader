#include "HeavyEnemyShip.h"
#include "Rocket.h"
#include "Config.h"

HeavyEnemyShip::HeavyEnemyShip()
	: EnemyShip(HEAVY_ENEMY_HEALTH, HEAVY_ENEMY_WIDTH, HEAVY_ENEMY_HEIGHT, HEAVY_ENEMY_PATH, HEAVY_ENEMY_SCORE)
{
	m_hurtImage = HEAVY_ENEMY_HIT_PATH;
	m_normalImage = HEAVY_ENEMY_PATH;
	m_enemyType = ENEMY_SHIP_HEAVY;

	Sprite* pHurt = Sprite::createWithSpriteFrameName(m_hurtImage);
	pHurt->setName(HURT_NAME);
	pHurt->setAnchorPoint(cocos2d::Vec2(0, 0));
	pHurt->setContentSize(cocos2d::Size(0, 0));
	this->addChild(pHurt);
}

void HeavyEnemyShip::getHit(Rocket* pRocket)
{
	this->m_health -= pRocket->power();
	cocos2d::Size sz = this->getContentSize();
	if (this->m_health >= 0) {
		auto* pHurt = this->getChildByName(HURT_NAME);
		pHurt->setContentSize(cocos2d::Size(0, 0));
		pHurt->setContentSize(sz);
	}
}

void HeavyEnemyShip::reset()
{
	this->m_health = m_fullHealth;
	cocos2d::Size sz = this->getContentSize();
	auto* pHurt = this->getChildByName(HURT_NAME);
	pHurt->setContentSize(cocos2d::Size(0, 0));
	this->setContentSize(sz);
}
