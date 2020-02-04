#pragma once
#include <string>

// define various constant value

// width, height constants
#define HEAVY_ENEMY_WIDTH		48.f
#define HEAVY_ENEMY_HEIGHT		48.f
#define LIGHT_ENEMY_WIDTH		48.f
#define LIGHT_ENEMY_HEIGHT		48.f

#define SPACE_SHIP_WIDTH		48.f
#define SPACE_SHIP_HEIGHT		48.f

#define ROCKET_WIDTH	12.f
#define ROCKET_HEIGHT	24.f


// image resource names
#define SPACE_SHIP_PATH "self.png"

#define LIGHT_ENEMY_PATH "enemy1.png"
#define HEAVY_ENEMY_PATH "enemy2.png"
#define HEAVY_ENEMY_HIT_PATH "enemy2_hit.png"

#define ROCKET_PATH "rocket.png"


// rocket power & enemy HP(Health Point)
#define DEFAULT_ROCKET_POWER 50.f

#define LIGHT_ENEMY_HEALTH 50.f
#define HEAVY_ENEMY_HEALTH 100.f




// sprite kind
#define TAG_GENERAL		0
#define TAG_ENEMY_SHIP	1
#define TAG_ROCKET		2
#define TAG_HEROSHIP	3

#define ENEMY_SHIP_HEAVY 0
#define ENEMY_SHIP_LIGHT 1


// Motion displacement
#define SHIP_DELTA_X			20.f
#define SHIP_DELTA_Y			2.1f
#define ROCKET_DELTA_Y			8.f

// Scene ids
#define SCENE_GAME_PLAY 0
#define SCENE_GAME_OVER 1


// shoot speed
#define ROCKET_RELOAD_RATE		.1f

// paths
#define BACKGROUND_PATH "background.png"

#define HURT_NAME "hurt"


// collision case
#define HERO_ENEMY_COLLISION 0
#define ROCKET_ENEMY_COLLISION 1

// scores
#define HEAVY_ENEMY_SCORE 20
#define LIGHT_ENEMY_SCORE 10