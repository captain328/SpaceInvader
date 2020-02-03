
#include "SpriteBase.h"
#include "Config.h"
#include "GameScene.h"
USING_NS_CC;

int SpriteBase::_spriteIncrement = 0;

SpriteBase::SpriteBase(float w, float h, std::string path)
{
	m_nSpriteId = _spriteIncrement++;
	if (!Sprite::initWithSpriteFrameName(path))
	{
		return;
	}

	setContentSize(cocos2d::Size(w, h));

	// set physics body to simulate collision
	PhysicsBody* rectBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	rectBody->setContactTestBitmask(true);
	this->setPhysicsBody(rectBody);
}

void SpriteBase::reset()
{
	// override if necessary
}
