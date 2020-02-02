#pragma once

// define various constant value
#define SHIP_WIDTH		48.f
#define SHIP_HEIGHT		48.f
#define ROCKET_WIDTH	12.f
#define ROCKET_HEIGHT	24.f

// agent sprite tag value
#define AGENT_SELF_TAG		65440
#define AGENT_ENEMY_TAG		65441
#define AGENT_ROCKET_TAG	65442

typedef enum _SPRITE_TYPE {
	ALIEN,
	ENEMY,
	ROCKET
} SPRITE_TYPE;

// Motion displacement
#define SHIP_DELTA_X			20.f
#define SHIP_DELTA_Y			.5f
#define ROCKET_DELTA_Y			14.f

// shoot speed
#define NORMAL_SPEED			.5f
