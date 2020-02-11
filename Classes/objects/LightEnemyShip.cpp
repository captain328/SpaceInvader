#include "LightEnemyShip.h"
#include "Rocket.h"
#include "Config.h"

LightEnemyShip::LightEnemyShip()
	: EnemyShip(LIGHT_ENEMY_HEALTH, LIGHT_ENEMY_WIDTH, LIGHT_ENEMY_HEIGHT, LIGHT_ENEMY_PATH, LIGHT_ENEMY_SCORE)
{
	m_enemyType = ENEMY_SHIP_LIGHT;
}

