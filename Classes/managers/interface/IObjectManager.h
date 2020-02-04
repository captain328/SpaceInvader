#ifndef __IOBJECT_MANAGER_H_
#define __IOBJECT_MANAGER_H_
#include <cocos2d.h>

class IObjectManager
{
protected:
	float visibleWidth;
	float visibleHeight;
	float originX;
	float originY;
	cocos2d::Scene* pGameScene;

public:
	virtual void setGameScene(cocos2d::Scene* pGameScene) { this->pGameScene = pGameScene; }

	virtual void initialize(float visibleWidth, float visibleHeight, float originX, float originY)
	{
		this->visibleWidth = visibleWidth;
		this->visibleHeight = visibleHeight;
		this->originX = originX;
		this->originY = originY;
	}

	virtual void update(float dt) = 0;
};
#endif // __IOBJECT_MANAGER_H_