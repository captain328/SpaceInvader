
#ifndef __SPRITE_FACTORY_H_
#define __SPRITE_FACTORY_H_

#include "Config.h"
#include <list>

class SpriteBase;

class SpriteFactory
{
private:
	SpriteFactory() {}
	static SpriteFactory* _instance;

public:
	virtual SpriteBase* create(int kind = -1);
	void push(SpriteBase*);

public:
	static SpriteFactory* instance();

private:
	SpriteBase* findFirstSpriteWithKind(int kind);

protected:
	std::list<SpriteBase*> _pool;
};

#endif
