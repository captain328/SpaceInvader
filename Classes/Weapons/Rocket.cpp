#include "Rocket.h"
#include "Config.h"

Rocket::Rocket(float power, float width, float height, std::string path)
	: SpriteBase(width, height, path)
{
	setTag(TAG_ROCKET);
	m_power = power;
}
