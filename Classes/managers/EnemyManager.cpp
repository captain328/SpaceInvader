#include "EnemyManager.h"
#include "Config.h"

USING_NS_CC;

EnemyManager* EnemyManager::_instance = nullptr;

EnemyManager* EnemyManager::instance()
{
    if (_instance == nullptr) {
        _instance = new EnemyManager();
    }
    return _instance;
}

EnemyManager::EnemyManager()
{
}

void EnemyManager::update(float dt)
{
	bool bEnemyExists = false;
	std::list<EnemyShip*>::iterator it;
	std::list<EnemyShip*> removeArray;
	for (it = pEnemies.begin(); it != pEnemies.end(); ++it) {
		EnemyShip* pEnemy = *it;
		float fEnemyY = pEnemy->getPositionY();
		pEnemy->setPositionY(fEnemyY - SHIP_DELTA_Y);
		
		if (pEnemy->getPositionY() < originY - SPACE_SHIP_HEIGHT)
		{
			// enemy is not in visible area
			pGameScene->removeChild(pEnemy);
			removeArray.push_back(pEnemy);
			addToPool(pEnemy);
		}
		else // enemy is in visible area
		{
			bEnemyExists = true;
		}
	}

	for (it = removeArray.begin(); it != removeArray.end(); ++it) {
		EnemyShip* pShip = *it;
		pShip->reset();
		pEnemies.remove(pShip);
	}

	if (!bEnemyExists) {
		generateTroop();
	}
}

void EnemyManager::addToPool(EnemyShip* pEnemy)
{
	switch (pEnemy->enemyType()) {
		case ENEMY_SHIP_HEAVY:
		{
			_heavyEnemyPool.returnObject((HeavyEnemyShip*)pEnemy);
			break;
		}
		case ENEMY_SHIP_LIGHT:
		{
			_lightEnemyPool.returnObject((LightEnemyShip*)pEnemy);
			break;
		}
	}
}

void EnemyManager::initialize(float visibleWidth, float visibleHeight, float originX, float originY)
{
	IObjectManager::initialize(visibleWidth, visibleHeight, originX, originY);
	m_level = 0;
	generateTroop();
}

void EnemyManager::levelUp(int level)
{
	m_level += level;
}


void EnemyManager::generateTroop()
{

	float xMargin = SPACE_SHIP_WIDTH / 2.f;

	float occu_width = SPACE_SHIP_WIDTH * 3.f / 2.f;
	float occu_height = SPACE_SHIP_HEIGHT * 3.f / 2.f;
	float delta_val = visibleWidth - xMargin * 2.f;
	int col_cnt = (int)(delta_val / occu_width + 1);
	int row_cnt = std::min(++m_level + 1, 5);
	m_level = row_cnt - 1;

	// arrange items in rows (2, 3, 4 and 5 rows of enemies, 5 is max)
	for (int j = 0; j < row_cnt; j++)
	{
		for (int i = 0; i < col_cnt; i++)
		{
			int nEnemyType = rand() % 2;
			// make random enemy ship
			EnemyShip* pEnemy = nullptr;
			if (nEnemyType == ENEMY_SHIP_HEAVY) {
				pEnemy = _heavyEnemyPool.getOne();
			}
			else {
				pEnemy = _lightEnemyPool.getOne();
			}
			pEnemies.push_back(pEnemy);

			pEnemy->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
			pEnemy->setPosition(Vec2(originX + xMargin + occu_width * i,
				visibleHeight + originY + occu_height * j));
			this->pGameScene->addChild(pEnemy);
		}
	}
}

void EnemyManager::kill(EnemyShip* pEnemy)
{
	pEnemies.remove(pEnemy);
	this->pGameScene->removeChild(pEnemy);
	if (pEnemy->enemyType() == ENEMY_SHIP_HEAVY) {
		HeavyEnemyShip* pHeavy = (HeavyEnemyShip*)pEnemy;
		pHeavy->reset();
		_heavyEnemyPool.returnObject(pHeavy);
	}
	else {
		_lightEnemyPool.returnObject((LightEnemyShip*)pEnemy);
	}
}

EnemyManager::~EnemyManager()
{
	_heavyEnemyPool.destroy();
	_lightEnemyPool.destroy();
}