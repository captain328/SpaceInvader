
#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

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
	void menuSpecialCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

private:
	void enableSpecialMenuItem(float dt = 0.f);
	void convertState(bool bSpecialMode);
	void generateEnemies(float dt = 0.f);
	void generateRockets(float dt = 0.f);
	void SetPhysicsWorld(cocos2d::PhysicsWorld *world) { m_sceneWorld = world; };
	void increaseScore();
	void showCrashState();

private:
	cocos2d::Label*				m_scoreLabel;		// score label
	cocos2d::Sprite*			m_progBarSprite;		// progress bar to show kill count in normal

	float						m_elapsed;			// time has elapsed
	float						m_rocketElapsed;		// time after last rocket
	bool						m_isTouchBegan;		// indicate if touch has begined
	float						m_touchXPos;			// touched x position

	int							m_killCntInNormal;	// kill enemy count in normal mode.
	int							m_level;
	cocos2d::PhysicsWorld *		m_sceneWorld;
};

#endif // __HELLOWORLD_SCENE_H__
