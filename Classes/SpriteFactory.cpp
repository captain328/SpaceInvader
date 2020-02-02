#include "SpriteFactory.h"
#include "SpriteBase.h"
#include "Config.h"
#include "SpaceShip.h"
#include "EnemyShip.h"
#include "Rocket.h"

SpriteFactory* SpriteFactory::_instance = NULL;

SpriteBase* SpriteFactory::create(int kind)
{
	if (_pool.empty()) {
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
				return new EnemyShip(HEAVY_ENEMY_HEALTH, HEAVY_ENEMY_WIDTH, HEAVY_ENEMY_HEIGHT, HEAVY_ENEMY_PATH);
			}
			case ENEMY_SHIP_LIGHT:
			{
				return new EnemyShip(LIGHT_ENEMY_HEALTH, LIGHT_ENEMY_WIDTH, LIGHT_ENEMY_HEIGHT, LIGHT_ENEMY_PATH);
			}
			default:
				return nullptr;
		}
	}

	// return first object as a default
	if (kind == -1)
	{
		SpriteBase* pFront = _pool.front();
		_pool.pop_back();
		return pFront;
	}
	return findFirstSpriteWithKind(kind);
}

SpriteBase* SpriteFactory::findFirstSpriteWithKind(int kind)
{
	std::list<SpriteBase*>::iterator it = _pool.begin();
	int nSpriteCnt = _pool.size();
	for (int i = 0; i < nSpriteCnt; i++)
	{
		SpriteBase* ithItem = *it;
		if (ithItem->spriteKind() == kind) {
			_pool.remove(ithItem);
			return ithItem;
		}
		advance(it, 1);
	}
	return nullptr;
}

void SpriteFactory::push(SpriteBase* p)
{
	_pool.push_back(p);
}

SpriteFactory* SpriteFactory::instance()
{
	if (_instance == NULL) {
		_instance = new SpriteFactory();
	}
	return _instance;
}
