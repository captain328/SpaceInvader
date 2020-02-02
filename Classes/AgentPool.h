
#ifndef __AGENT_POOL_H_
#define __AGENT_POOL_H_

#include "Config.h"
#include <list>

class AgentSprite;

class AgentPool
{
private:
	AgentPool() {}

public:
	static AgentPool* getInstance();
	AgentSprite* getAgent(int);
	void returnAgent(AgentSprite*);

private:
	static AgentPool* _pInstance;
	std::list<AgentSprite*> _enemyVec;
	std::list<AgentSprite*> _rocketVec;
};

#endif
