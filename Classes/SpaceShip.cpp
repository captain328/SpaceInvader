#include "Config.h"
#include "SpaceShip.h"
#include "Rocket.h"
#include "SpriteFactory.h"

SpaceShip::SpaceShip(float width, float height, std::string path)
	: SpriteBase(width, height, path)
{
	setTag(TAG_SPACESHIP);
}

Rocket* SpaceShip::fire()
{
	Rocket* rocketSprite = (Rocket*)(SpritePool::instance()->create(TAG_ROCKET));
	if (rocketSprite == nullptr) {
		printf("rocket creation failed.");
	}
	else {

		rocketSprite->setPositionX(this->getPositionX());
		rocketSprite->setPositionY(this->getPositionY() + this->getContentSize().height);
	}
	return rocketSprite;
}