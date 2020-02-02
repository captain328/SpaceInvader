#include "CollisionManager.h"
#include "Config.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "SpriteBase.h"
#include "HeavyEnemyShip.h"
#include "LightEnemyShip.h"
#include "Rocket.h"
#include "SpritePool.h"
#include "MenuManager.h"

USING_NS_CC;

CollisionManager* CollisionManager::_instance = nullptr;

CollisionManager* CollisionManager::instance() {
	if (_instance == nullptr) {
		_instance = new CollisionManager();
	}
	return _instance;
}

CollisionManager::CollisionManager()
{
	// nothing to do here
}

void CollisionManager::setGameScene(GameScene* pScene)
{
	pGameScene = pScene;
}

bool CollisionManager::handleContact(SpriteBase* p1, SpriteBase* p2)
{
	// in case of collision between rocket and ship
	if ((p1->getTag() == TAG_ROCKET
		&& p2->getTag() == TAG_ENEMY_SHIP)
		|| (p2->getTag() == TAG_ROCKET
			&& p1->getTag() == TAG_ENEMY_SHIP))
	{
		// rocket collide with enemy
		Rocket* pRocket = (Rocket*)(p1->getTag() == TAG_ROCKET ? p1 : p2);
		Enemy* pEnemyShip = (Enemy*)(p1->getTag() == TAG_ENEMY_SHIP ? p1 : p2);
		Enemy* pEnemy = nullptr;
		if (pEnemyShip->enemyType() == ENEMY_SHIP_HEAVY)
		{
			pEnemy = (HeavyEnemyShip*)pEnemyShip;
		}
		else {
			pEnemy = (LightEnemyShip*)pEnemyShip;
		}
		// force healthpoint reduction
		pEnemy->getHit(pRocket);
		if (pEnemy->isDead())
		{
			pGameScene->removeChild((SpriteBase*)pEnemyShip);
			// it is dead and it has to be pushed into pool
			SpritePool::instance()->push((SpriteBase*)pEnemyShip);
			pGameScene->increaseScore();
		}
		pGameScene->removeChild(pRocket);
		// rocket must go to pool once it is collided with someone
		SpritePool::instance()->push(pRocket);
	}
	else if (p1->getTag() == TAG_SPACESHIP
		|| p2->getTag() == TAG_SPACESHIP)
	{	// collision between spaceship and enemyship
		// here is game over case
		// collision between spaceship and enemyship
		pGameScene->stopAllActions();
		MenuManager::instance()->switchScene(SCENE_GAME_OVER);
		return false;
	}
	return true;
}