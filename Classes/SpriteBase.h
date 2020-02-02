
#ifndef __Agent_SPRITE_H__
#define __Agent_SPRITE_H__

#include "cocos2d.h"

class SpriteBase : public cocos2d::Sprite
{
private:
	bool m_bValid;
	int m_nSpriteKind;
public:
	SpriteBase(float w, float h, std::string path);
	bool isValid() { return m_bValid; }
	int spriteKind() { return m_nSpriteKind; }
	void SetSpriteKind(int kind);
};

#endif // __AGENT_SPRITE_H__
