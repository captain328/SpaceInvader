
#ifndef __Agent_SPRITE_H__
#define __Agent_SPRITE_H__

#include "cocos2d.h"
#include "Config.h"

class SpriteBase : public cocos2d::Sprite
{
public:
    static SpriteBase* createSprite(int);

    virtual bool init();
	void reset();
};

#endif // __AGENT_SPRITE_H__
