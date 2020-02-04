#pragma once
#include "Pool.h"
#include "IObjectManager.h"
#include "HeavyEnemyShip.h"
#include "LightEnemyShip.h"


class EnemyManager : public IObjectManager
{
private:
    static EnemyManager* _instance;

public:
    static EnemyManager* instance();

public:
	EnemyManager();
    void update(float dt);
	void initialize(float visibleWidth, float visibleHeight, float originX, float originY);
	void levelUp(int level=1);
	void kill(EnemyShip* pEnemy);
private:
	void generateTroop();
	void addToPool(EnemyShip* pEnemy);
private:
    Pool<HeavyEnemyShip> _heavyEnemyPool;
    Pool<LightEnemyShip> _lightEnemyPool;
	std::list<EnemyShip*> pEnemies;
	int m_level;
};
