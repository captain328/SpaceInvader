
#include "Agent.h"

USING_NS_CC;

AgentSprite* AgentSprite::createSprite(int atag)
{
	AgentSprite* sprite = new AgentSprite;
	if (sprite != nullptr) 
	{
		sprite->setTag(atag);
		sprite->init();
		//sprite->autorelease();
	}
    return sprite;
}

// on "init" you need to initialize your instance
bool AgentSprite::init()
{
	// Set resource file name according to its type
	std::string rsrcFileName;
	
	if (getTag() == AGENT_SELF_TAG)
	{
		rsrcFileName = StringUtils::format("self.png");
	}
	else if (getTag() == AGENT_ENEMY_TAG)
	{
		rsrcFileName = StringUtils::format("enemy1.png");
	}
	else if (getTag() == AGENT_ROCKET_TAG)
	{
		rsrcFileName = StringUtils::format("rocket.png");
	}

    if ( !Sprite::initWithFile(rsrcFileName) )
    {
        return false;
    }
	
	// if this type is enemy, then flip y
	if (getTag() == AGENT_SELF_TAG)
	{
		setContentSize(cocos2d::Size(SHIP_WIDTH, SHIP_HEIGHT));
	}
	else if (getTag() == AGENT_ENEMY_TAG)
	{
		setContentSize(cocos2d::Size(SHIP_WIDTH, SHIP_HEIGHT));
		setFlippedY(true);
	}
	else if (getTag() == AGENT_ROCKET_TAG)
	{
		setContentSize(cocos2d::Size(ROCKET_WIDTH, ROCKET_HEIGHT));
	}

	// set physics body to simulate collision
	auto rectBody = PhysicsBody::createBox(this->getContentSize(), PHYSICSBODY_MATERIAL_DEFAULT);
	rectBody->setContactTestBitmask(true);
	this->setPhysicsBody(rectBody);

    return true;
}

void AgentSprite::reset()
{
	//RESET!
}
