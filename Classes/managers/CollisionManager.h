#pragma once
#include "cocos2d.h"

class GameScene;
class SpriteBase;
class HeroShip;
class EnemyShip;
class Rocket;

class CollisionManager
{
private:
	static CollisionManager* _instance;
	GameScene* pGameScene;
public:
	CollisionManager();
	void setGameScene(GameScene* pScene);
	static CollisionManager* instance();
	bool handleHeroEnemyCollision(HeroShip* pHero, EnemyShip* pEnemy);
	bool handleRocketEnemyCollision(Rocket* pRocket, EnemyShip* pEnemy);
};

