
#include "SpriteBase.h"
#include "Config.h"
USING_NS_CC;

SpriteBase::SpriteBase(float w, float h, std::string path)
{
	m_nSpriteKind = TAG_GENERAL;

	if (!Sprite::initWithFile(path))
	{
		m_bValid = false;
		return;
	}

	setContentSize(cocos2d::Size(w, h));

	// set physics body to simulate collision
	PhysicsBody* rectBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	rectBody->setContactTestBitmask(true);
	this->setPhysicsBody(rectBody);
	m_bValid = true;
}

void SpriteBase::SetSpriteKind(int kind)
{
	m_nSpriteKind = kind;
	setTag(kind);
}