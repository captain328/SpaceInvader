#include "HeroManager.h"
#include "HeroShip.h"
#include "Config.h"
#include "RocketManager.h"

USING_NS_CC;

HeroManager* HeroManager::_instance = nullptr;

HeroManager* HeroManager::instance()
{
    if (_instance == nullptr) {
        _instance = new HeroManager();
    }
    return _instance;
}

HeroManager::HeroManager()
{
    m_pHeroShip = new HeroShip();
	m_bTouchBegan = false;
	m_fRocketReloadTimer = 0.f;
}

void HeroManager::update(float dt)
{
	if (m_bTouchBegan)
	{
		float curx = m_pHeroShip->getPositionX();
		if (curx + SHIP_DELTA_X <= std::min(m_touchX, visibleWidth - SPACE_SHIP_WIDTH / 2))
		{
			m_pHeroShip->setPositionX(curx + SHIP_DELTA_X);
		}
		else if (curx - SHIP_DELTA_X >= std::max(m_touchX, SPACE_SHIP_WIDTH / 2))
		{
			m_pHeroShip->setPositionX(curx - SHIP_DELTA_X);
		}
	}
	// launch rocket
	m_fRocketReloadTimer += dt;
	if (m_fRocketReloadTimer >= ROCKET_RELOAD_RATE) {
		reloadRocket();
		RocketManager::instance()->launch(m_pHeroShip->getPositionX(), m_pHeroShip->getPositionY());
	}
}

void HeroManager::reloadRocket()
{
	m_fRocketReloadTimer = 0.f;
}

void HeroManager::initialize(float visibleWidth, float visibleHeight, float originX, float originY)
{
	IObjectManager::initialize(visibleWidth, visibleHeight, originX, originY);
	Size shipSize = m_pHeroShip->getContentSize();
	m_pHeroShip->setPosition(visibleWidth / 2 + originX, shipSize.height * 3 + originY);
	pGameScene->addChild(m_pHeroShip);
}

void HeroManager::onTouchBegan(float touchX, float touchY)
{
	m_bTouchBegan = true;
	m_touchX = touchX;
	m_touchY = touchY;
}

void HeroManager::onTouchMoved(float touchX, float touchY)
{
	m_touchX = touchX;
	m_touchY = touchY;
}

void HeroManager::onTouchEnded(float touchX, float touchY)
{
	m_touchX = touchX;
	m_touchY = touchY;
	m_bTouchBegan = false;
}

HeroManager::~HeroManager()
{
	delete m_pHeroShip;
}