#include "SpaceShip.h"
#include "Config.h"

SpaceShip::SpaceShip(float width, float height, std::string path)
	: SpriteBase(width, height, path)
{
	SetSpriteKind(TAG_SPACESHIP);
}
