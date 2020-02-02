
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class SpriteFactory;
class SpaceShip;

class GameScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
	virtual void update(float dt);

	// touch event listener
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event); 
	bool onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
	bool onContactBegin(cocos2d::PhysicsContact &contact);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	void generateEnemies(float dt = 0.f);
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { m_sceneWorld = world; };
	void increaseScore();

private:
	cocos2d::Label*				m_scoreLabel;		// score label

	float						m_elapsed;			// time has elapsed
	float						m_rocketReloadTimer;		// time after last rocket
	bool						m_bTouchBegan;		// indicate if touch has begined
	float						m_touchXPos;			// touched x position

	int							m_level;
	cocos2d::PhysicsWorld *		m_sceneWorld;
};

#endif // __HELLOWORLD_SCENE_H__
