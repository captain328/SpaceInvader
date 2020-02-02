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
			// SpaceShip(self ship) has only width, height, image path properties.
			return new SpaceShip(SPACE_SHIP_WIDTH, SPACE_SHIP_HEIGHT, SPACE_SHIP_PATH);
		}
		case TAG_ROCKET:
		{
			// rocket has power extra
			return new Rocket(DEFAULT_ROCKET_POWER, ROCKET_WIDTH, ROCKET_HEIGHT, ROCKET_PATH);
		}
		case ENEMY_SHIP_HEAVY:
		{
			// Heavy enemy ship has health point it is given from constant HEAVY_ENEMY_HEALTH
			return new HeavyEnemyShip(HEAVY_ENEMY_HEALTH, HEAVY_ENEMY_WIDTH, HEAVY_ENEMY_HEIGHT, HEAVY_ENEMY_PATH);
		}
		case ENEMY_SHIP_LIGHT:
		{
			// same as above
			// uses different class instance
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
	// a little complicated in look
	// but it's easy once you understand
	std::list<SpriteBase*>::iterator it = _pool.begin();

	// object count stored in the pool
	int nSpriteCnt = _pool.size();
	for (int i = 0; i < nSpriteCnt; i++)
	{
		// go thru all items in the _pool
		SpriteBase* ithItem = *it;
		if (ithItem->getTag() == tag) {
			// if iTh item has the Tag of tag
			// remove it from _pool ( because it is selected to for use again )
			// and return it
			_pool.remove(ithItem);
			return ithItem;
		}
		advance(it, 1);
	}
	// otherwise, there isn't any object and return null pointer
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
	// this is the one for SpriteFactory Singleton
	if (_instance == NULL) {
		// uses static method and static member variable to store singleton object instance
		_instance = new SpritePool();
	}
	return _instance;
}
