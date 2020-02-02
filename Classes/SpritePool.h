
#ifndef __SPRITE_POOL_H_
#define __SPRITE_POOL_H_

#include "Config.h"
#include <list>

class SpriteBase;

class SpritePool
{
private:
	SpritePool() {}
	static SpritePool* _instance;

public:
	virtual SpriteBase* create(int kind = -1);
	void push(SpriteBase*);

public:
	static SpritePool* instance();

private:
	SpriteBase* findFirstSpriteWithTag(int tag);

protected:
	// list for storing objects
	std::list<SpriteBase*> _pool;
};

#endif
