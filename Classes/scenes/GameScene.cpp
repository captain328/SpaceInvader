/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "GameScene.h"
#include "HeroManager.h"
#include "HeroShip.h"
#include "EnemyManager.h"
#include "RocketManager.h"
#include "CollisionManager.h"
#include "Config.h"
USING_NS_CC;

Scene* GameScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);
    return scene;
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("sprites.plist");

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto dispLabel = Label::createWithTTF("Score : ", "fonts/arial.ttf", 24);
	if (dispLabel == nullptr)
	{
		printf("'fonts/arial.ttf' is missing.");
	}
	else
	{
		// position the label on the top left of the screen
		dispLabel->setPosition(Vec2(origin.x + 50, origin.y + visibleSize.height - 30));

		// add the label as a child to this layer
		this->addChild(dispLabel, 10);
	}

	// add background
	auto sprite = Sprite::create(BACKGROUND_PATH);
	if (sprite == nullptr) {
		printf("'background.png' is missing.");
	}
	else
	{
		// position the sprite on the center of the screen
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

		// add the sprite as a child to this layer
		this->addChild(sprite, 0);
	}


	m_scoreLabel = Label::createWithTTF("0", "fonts/arial.ttf", 24);
	if (m_scoreLabel == nullptr)
	{
		printf("'fonts/arial.ttf' is missing.");
	}
	else
	{
		// position the label on the center of the screen
		m_scoreLabel->setPosition(Vec2(
			dispLabel->getPositionX() + dispLabel->getContentSize().width + 5.f,
			dispLabel->getPositionY()));

		// add the label as a child to this layer
		this->addChild(m_scoreLabel, 10);
	}
	
	// 2. game code
	pHeroManager = HeroManager::instance();
	pEnemyManager = EnemyManager::instance();
	pRocketManager = RocketManager::instance();
	pCollisionManager = CollisionManager::instance();
	pHeroManager->setGameScene(this);
	pEnemyManager->setGameScene(this);
	pRocketManager->setGameScene(this);
	pCollisionManager->setGameScene(this);

	pHeroManager->initialize(visibleSize.width, visibleSize.height, origin.x, origin.y);
	pEnemyManager->initialize(visibleSize.width, visibleSize.height, origin.x, origin.y);
	pRocketManager->initialize(visibleSize.width, visibleSize.height, origin.x, origin.y);

//  adding event handlers
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(GameScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	scheduleUpdate();

    return true;
}

void GameScene::update(float dt)
{
	pHeroManager->update(dt);
	pEnemyManager->update(dt);
	pRocketManager->update(dt);
}

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	Vec2 touchLocation = touch->getLocation();
	HeroManager::instance()->onTouchBegan(touchLocation.x, touchLocation.y);
	return true;
}

bool GameScene::onTouchMoved(Touch *touch, Event *event)
{
	Vec2 touchLocation = touch->getLocation();
	HeroManager::instance()->onTouchMoved(touchLocation.x, touchLocation.y);
	return true;
}

bool GameScene::onTouchEnded(Touch *touch, Event *event)
{
	Vec2 touchLocation = touch->getLocation();
	HeroManager::instance()->onTouchEnded(touchLocation.x, touchLocation.y);
	return true;
}

// Handle collision event
bool GameScene::onContactBegin(PhysicsContact &contact)
{
	Node* shapeA = contact.getShapeA()->getBody()->getNode();
	Node* shapeB = contact.getShapeB()->getBody()->getNode();

	// cases
	// heroship:enemyship => game over
	// rocket:enemyship => enemy hit
	int tagA = shapeA->getTag();
	int tagB = shapeB->getTag();
	int nCollisionCase = -1;
	
	if ((tagA == TAG_HEROSHIP && tagB == TAG_ENEMY_SHIP) || 
		(tagB == TAG_HEROSHIP && tagA == TAG_ENEMY_SHIP)) {
		nCollisionCase = HERO_ENEMY_COLLISION;
	}
	if ((tagA == TAG_ROCKET && tagB == TAG_ENEMY_SHIP) || 
		(tagB == TAG_ROCKET && tagA == TAG_ENEMY_SHIP))
	{
		nCollisionCase = ROCKET_ENEMY_COLLISION;
	}

	switch (nCollisionCase) {
		case HERO_ENEMY_COLLISION:
		{
			HeroShip* pHero = (HeroShip*)(tagA == TAG_HEROSHIP ? shapeA : shapeB);
			EnemyShip* pEnemy = (EnemyShip*)(tagA == TAG_ENEMY_SHIP ? shapeA : shapeB);
			return pCollisionManager->handleHeroEnemyCollision(pHero, pEnemy);
		}
		case ROCKET_ENEMY_COLLISION:
		{
			Rocket* pRocket = (Rocket*)(tagA == TAG_ROCKET ? shapeA : shapeB);
			EnemyShip* pEnemy = (EnemyShip*)(tagA == TAG_ENEMY_SHIP ? shapeA : shapeB);
			return pCollisionManager->handleRocketEnemyCollision(pRocket, pEnemy);
		}
		default:
		{
			return true;
		}
	}
	return true;
}

void GameScene::increaseScore(int scorePoint)
{
	int curscore = std::atoi(m_scoreLabel->getString().c_str());
	curscore += scorePoint;
	m_scoreLabel->setString(StringUtils::format("%d", curscore));
}
