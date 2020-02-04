#pragma once
#include "Pool.h"
#include "IObjectManager.h"
#include "cocos2d.h"
#include "SimpleRocket.h"

class RocketManager : public IObjectManager
{
private:
    static RocketManager* _instance;

public:
    static RocketManager* instance();

public:
	RocketManager();
    void update(float dt);
	void initialize(float visibleWidth, float visibleHeight, float originX, float originY);
	void launch(float launchX, float launchY);

private:
	void addToPool(Rocket* pRocket);
private:
    Pool<SimpleRocket> _rocketPool;
	std::list<Rocket*> pRockets;
};
