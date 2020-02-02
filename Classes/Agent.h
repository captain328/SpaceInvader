
#ifndef __Agent_SPRITE_H__
#define __Agent_SPRITE_H__

#include "cocos2d.h"
#include "Config.h"

class AgentSprite : public cocos2d::Sprite
{
public:
    static AgentSprite* createSprite(int);

    virtual bool init();
	void reset();
};

#endif // __AGENT_SPRITE_H__
