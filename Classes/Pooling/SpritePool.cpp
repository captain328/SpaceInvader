#include "SpritePool.h"
#include "SpriteBase.h"
#include "Config.h"
#include "SpaceShip.h"
#include "HeavyEnemyShip.h"
#include "LightEnemyShip.h"
#include "Rocket.h"

SpritePool* SpritePool::_instance = NULL;

/*
* find or create 
*/
SpriteBase* SpritePool::create(int kind)
{
	// I explaind here.
	// try to find object using findFirstSpriteWithTag method
	SpriteBase* pFound = findFirstSpriteWithTag(kind);
	if (pFound != nullptr)
	{
		return pFound;
	}

	// if null
	// make object using specific classes
	switch (kind)
	{
		case TAG_SPACESHIP:
		{
			return new SpaceShip(SPACE_SHIP_WIDTH, SPACE_SHIP_HEIGHT, SPACE_SHIP_PATH);
		}
		case TAG_ROCKET:
		{
			return new Rocket(DEFAULT_ROCKET_POWER, ROCKET_WIDTH, ROCKET_HEIGHT, ROCKET_PATH);
		}
		case ENEMY_SHIP_HEAVY:
		{
			return new HeavyEnemyShip(HEAVY_ENEMY_HEALTH, HEAVY_ENEMY_WIDTH, HEAVY_ENEMY_HEIGHT, HEAVY_ENEMY_PATH);
		}
		case ENEMY_SHIP_LIGHT:
		{
			return new LightEnemyShip(LIGHT_ENEMY_HEALTH, LIGHT_ENEMY_WIDTH, LIGHT_ENEMY_HEIGHT, LIGHT_ENEMY_PATH);
		}
		default:
			return nullptr;
	}	
}

/*
* retrieve first sprite object with tag id
*/
SpriteBase* SpritePool::findFirstSpriteWithTag(int tag)
{
	std::list<SpriteBase*>::iterator it = _pool.begin();

	int nSpriteCnt = _pool.size();
	for (int i = 0; i < nSpriteCnt; i++)
	{
		SpriteBase* ithItem = *it;
		if (ithItem->getTag() == tag) {
			_pool.remove(ithItem);
			return ithItem;
		}
		advance(it, 1);
	}
	return nullptr;
}

/*
* push object to pool for reuse
*/
void SpritePool::push(SpriteBase* p)
{
	p->reset();
	_pool.push_back(p);
}

SpritePool* SpritePool::instance()
{
	if (_instance == NULL) {
		_instance = new SpritePool();
	}
	return _instance;
}
