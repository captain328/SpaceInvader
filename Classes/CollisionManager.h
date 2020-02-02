#pragma once
#include "cocos2d.h"

class GameScene;
class SpriteBase;

class CollisionManager
{
private:
	static CollisionManager* _instance;
	GameScene* pGameScene;
public:
	CollisionManager();
	void setGameScene(GameScene* pScene);
	static CollisionManager* instance();
	bool handleContact(SpriteBase* p1, SpriteBase* p2);
};

