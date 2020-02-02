
#ifndef __AGENT_POOL_H_
#define __AGENT_POOL_H_

#include "Config.h"
#include <list>

class SpriteBase;

class SpriteFactory
{
private:
	SpriteFactory() {}

public:
	static SpriteFactory* instance();
	SpriteBase* getAgent(int);
	void returnAgent(SpriteBase*);

private:
	static SpriteFactory* _pInstance;
	std::list<SpriteBase*> _enemyVec;
	std::list<SpriteBase*> _rocketVec;
};

#endif
