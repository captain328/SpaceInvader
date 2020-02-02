
#ifndef __SPRITE_BASE_H__
#define __SPRITE_BASE_H__

#include "cocos2d.h"

class SpriteBase : public cocos2d::Sprite
{
private:
	static int _spriteIncrement;
private:
	int m_nSpriteId;
public:
	int spriteId() { return m_nSpriteId; }
	SpriteBase(float w, float h, std::string path);
	virtual void reset();
};

#endif // __SPRITE_BASE_H__
