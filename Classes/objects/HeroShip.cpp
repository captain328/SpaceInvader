#include "Config.h"
#include "HeroShip.h"
#include "Rocket.h"
#include "SpriteBase.h"

HeroShip::HeroShip()
	: SpriteBase(SPACE_SHIP_WIDTH, SPACE_SHIP_HEIGHT, SPACE_SHIP_PATH)
{
	setTag(TAG_HEROSHIP);
}

Rocket* HeroShip::fire()
{
	// Rocket* rocketSprite = (Rocket*)(SpritePool::instance()->create(TAG_ROCKET));
	// if (rocketSprite == nullptr) {
	// 	printf("rocket creation failed.");
	// }
	// else {

	// 	rocketSprite->setPositionX(this->getPositionX());
	// 	rocketSprite->setPositionY(this->getPositionY() + this->getContentSize().height);
	// }
	// return rocketSprite;
	return nullptr;
}