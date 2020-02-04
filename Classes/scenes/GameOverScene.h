
#ifndef __GAMEOVER_SCENE_H__
#define __GAMEOVER_SCENE_H__

#include "cocos2d.h"

class GameOverScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);

private:
	void menuExitCallback(Ref* sender);
	void menuRetryCallback(Ref* sender);
};

#endif // __HELLOWORLD_SCENE_H__
