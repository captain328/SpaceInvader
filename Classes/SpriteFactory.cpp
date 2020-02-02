#include "SpriteFactory.h"
#include "SpriteBase.h"

SpriteFactory* SpriteFactory::_pInstance = nullptr;

/**
* Static method for accessing class instance.
*
* @return AgentPool instance.
*/
SpriteFactory* SpriteFactory::instance()
{
	if (_pInstance == nullptr) {
		_pInstance = new SpriteFactory;
	}
	return _pInstance;
}

/**
* Returns instance of agent with given agent type.
*
* New agent will be created if all the agents
* were used at the time of the request.
*
* @return agent instance.
*/
SpriteBase* SpriteFactory::getAgent(int atag)
{
	if ((atag == AGENT_ROCKET_TAG && _rocketVec .empty()) 
			|| (atag == AGENT_ENEMY_TAG && _enemyVec.empty())
			|| atag == AGENT_SELF_TAG)
	{
		return SpriteBase::createSprite(atag);
	}
	else if (atag == AGENT_ROCKET_TAG) 
	{
		SpriteBase* resource = _rocketVec.front();
		_rocketVec.pop_front();
		return resource;
	}
	else if (atag == AGENT_ENEMY_TAG)
	{
		SpriteBase* resource = _enemyVec.front();
		_enemyVec.pop_front();
		return resource;
	}
}

/**
* Return agent back to the pool.
*
* The agent must be initialized back to
* the default settings before someone else
* attempts to use it.
*
* @param object object instance.
* @return void
*/
void SpriteFactory::returnAgent(SpriteBase* object)
{
	object->reset();
	if (object->getTag() == AGENT_ROCKET_TAG) 
	{
		_rocketVec.push_back(object);
	}
	else if (object->getTag() == AGENT_ENEMY_TAG)
	{
		_enemyVec.push_back(object);
	}
}
