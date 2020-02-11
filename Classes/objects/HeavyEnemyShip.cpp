#include "HeavyEnemyShip.h"
#include "Rocket.h"
#include "Config.h"

HeavyEnemyShip::HeavyEnemyShip()
	: EnemyShip(HEAVY_ENEMY_HEALTH, HEAVY_ENEMY_WIDTH, HEAVY_ENEMY_HEIGHT, HEAVY_ENEMY_PATH, HEAVY_ENEMY_SCORE)
{
	m_hurtImage = HEAVY_ENEMY_HIT_PATH;
	m_normalImage = HEAVY_ENEMY_PATH;
	m_enemyType = ENEMY_SHIP_HEAVY;
}

