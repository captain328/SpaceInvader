#include "Enemy.h"
#include "SpriteBase.h"
#include "Config.h"
#include "Rocket.h"

#define HEALTH_BAR_RATIO 5.f

EnemyShip::EnemyShip(float health, float width, float height, std::string path, int scorePoint)
	: SpriteBase(width, height, path)
{
	m_health = health;
	m_fullHealth = m_health;
	setTag(TAG_ENEMY_SHIP);
	m_scorePoint = scorePoint;
	setFlippedY(true);

	Sprite* pHealthBar = Sprite::createWithSpriteFrameName(HEALTH_BAR_PATH);
	pHealthBar->setName(HEALTH_BAR);
	pHealthBar->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	cocos2d::Size szHealthBar(width, width/HEALTH_BAR_RATIO);
	pHealthBar->setContentSize(szHealthBar);
	this->addChild(pHealthBar);
}

void EnemyShip::getHit(Rocket* pRocket)
{
	this->m_health -= pRocket->power();
	resetHealthBar();
}

void EnemyShip::reset()
{
	this->m_health = this->m_fullHealth;
	resetHealthBar();
}

void EnemyShip::resetHealthBar()
{
	float fWidth = getContentSize().width;
	auto pHealthBar = this->getChildByName(HEALTH_BAR);
	cocos2d::Size healthBarSize = pHealthBar->getContentSize();
	healthBarSize.width = fWidth * this->m_health / this->m_fullHealth;
	pHealthBar->setContentSize(healthBarSize);
}
