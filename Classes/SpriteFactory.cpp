#include "SpriteFactory.h"
#include "SpriteBase.h"
#include "Config.h"
#include "SpaceShip.h"
#include "EnemyShip.h"
#include "Rocket.h"

SpriteFactory* SpriteFactory::_instance = NULL;

SpriteBase* SpriteFactory::create(int kind)
{
	SpriteBase* pFound = findFirstSpriteWithKind(kind);
	if (pFound != nullptr)
	{
		return pFound;
	}
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
	p->reset();
	_pool.push_back(p);
}

SpriteFactory* SpriteFactory::instance()
{
	if (_instance == NULL) {
		_instance = new SpriteFactory();
	}
	return _instance;
}
