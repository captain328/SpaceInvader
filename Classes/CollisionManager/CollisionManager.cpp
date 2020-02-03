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

bool CollisionManager::handleContact(SpriteBase* shapeA, SpriteBase* shapeB)
{
	// in case of collision between rocket and ship
	if ((shapeA->getTag() == TAG_ROCKET
		&& shapeB->getTag() == TAG_ENEMY_SHIP)
		|| (shapeB->getTag() == TAG_ROCKET
			&& shapeA->getTag() == TAG_ENEMY_SHIP))
	{
		// rocket collide with enemy
		Rocket* pRocket = (Rocket*)(shapeA->getTag() == TAG_ROCKET ? shapeA : shapeB);
		Enemy* pEnemyShip = (Enemy*)(shapeA->getTag() == TAG_ENEMY_SHIP ? shapeA : shapeB);
		Enemy* pEnemy = nullptr;
		if (pEnemyShip->enemyType() == ENEMY_SHIP_HEAVY)
		{
			pEnemy = (HeavyEnemyShip*)pEnemyShip;
		}
		else {
			pEnemy = (LightEnemyShip*)pEnemyShip;
		}
		pEnemy->getHit(pRocket);
		if (pEnemy->isDead())
		{
			pGameScene->removeChild((SpriteBase*)pEnemyShip);
			SpritePool::instance()->push((SpriteBase*)pEnemyShip);
			pGameScene->increaseScore();
		}
		pGameScene->removeChild(pRocket);
		SpritePool::instance()->push(pRocket);
	}
	else if (shapeA->getTag() == TAG_SPACESHIP
		|| shapeB->getTag() == TAG_SPACESHIP)
	{	// collision between spaceship and enemyship
		pGameScene->stopAllActions();
		MenuManager::instance()->switchScene(SCENE_GAME_OVER);
		return false;
	}
	return true;
}