#include "CollisionManager.h"
#include "Config.h"
#include "GameOverScene.h"
#include "GameScene.h"
#include "SpriteBase.h"
#include "Rocket.h"
#include "MenuManager.h"
#include "EnemyManager.h"
#include "Enemy.h"


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

bool CollisionManager::handleHeroEnemyCollision(HeroShip* pHero, EnemyShip* pEnemy)
{
	pGameScene->stopAllActions();
	MenuManager::instance()->switchScene(SCENE_GAME_OVER);
	return true;
}

bool CollisionManager::handleRocketEnemyCollision(Rocket* pRocket, EnemyShip* pEnemy)
{
	pEnemy->getHit(pRocket);
	if (pEnemy->isDead())
	{
		EnemyManager::instance()->kill(pEnemy);
		pGameScene->increaseScore(pEnemy->scorePoint());
	}
	pGameScene->removeChild(pRocket);
	return true;
}
