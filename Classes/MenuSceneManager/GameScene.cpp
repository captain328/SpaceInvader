#include <stdlib.h>
#include "GameScene.h"
#include "GameOverScene.h"
#include "SpriteBase.h"
#include "SpritePool.h"
#include "Config.h"
#include "SpaceShip.h"
#include "Rocket.h"
#include "HeavyEnemyShip.h"
#include "LightEnemyShip.h"
#include "Enemy.h"
#include "MenuManager.h"
#include "CollisionManager.h"

USING_NS_CC;

SpriteBatchNode* GameScene::spritebatch = nullptr;


Scene* GameScene::createScene()
{

	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));

	auto layer = GameScene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());

	scene->addChild(layer);

	
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // super init first
    if ( !Scene::init() )
    {
        return false;
    }
	SpriteFrameCache* cache = SpriteFrameCache::getInstance();
	cache->addSpriteFramesWithFile("sprites.plist");


	CollisionManager::instance()->setGameScene(this);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a label shows game title
    // create and initialize a label

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
    // add background
    auto sprite = Sprite::create(BACKGROUND_PATH);
    if (sprite == nullptr) {
		printf("'background.png' is missing.");
    }
    else
    {
        // position the sprite on the center of the screen
		sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

	// add space ship
	SpaceShip* spaceShip = (SpaceShip*)SpritePool::instance()->create(TAG_SPACESHIP);
	if (spaceShip == nullptr) {
		printf("space ship creation failed.");
	}
	else {
		spaceShip->setPosition(Vec2(visibleSize.width / 2 + origin.x, SPACE_SHIP_HEIGHT * 3 + origin.y));
		this->addChild(spaceShip, 1);
	}
	
	m_bTouchBegan = false;
	m_elapsed = 0.f;
	m_rocketReloadTimer = 0.f;

	// add event handlers
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

bool GameScene::onTouchBegan(Touch *touch, Event *event)
{
	m_bTouchBegan = true;
	m_touchXPos = touch->getLocation().x;
	return true;
}

bool GameScene::onTouchMoved(Touch *touch, Event *event)
{
	m_touchXPos = touch->getLocation().x;
	return true;
}

bool GameScene::onTouchEnded(Touch *touch, Event *event)
{
	m_bTouchBegan = false;
	return true;
}

// Handle collision event
bool GameScene::onContactBegin(PhysicsContact &contact)
{
	// collision is made between two objects
	Node* shapeA = contact.getShapeA()->getBody()->getNode();
	Node* shapeB = contact.getShapeB()->getBody()->getNode();

	if (!((shapeA->getTag() <= TAG_SPACESHIP && shapeA->getTag() >= TAG_ENEMY_SHIP) &&
		(shapeB->getTag() <= TAG_SPACESHIP && shapeB->getTag() >= TAG_ENEMY_SHIP)))
	{
		// out of our handling
		return true;
	}
	SpriteBase* pSpriteA = (SpriteBase*)shapeA;
	SpriteBase* pSpriteB = (SpriteBase*)shapeB;

	return CollisionManager::instance()->handleContact(pSpriteA, pSpriteB);
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

/**
* increase score
*/
void GameScene::increaseScore()
{
	int curscore = std::atoi(m_scoreLabel->getString().c_str());
	curscore += 20;
	m_scoreLabel->setString(StringUtils::format("%d", curscore));
}

/**
* generate enemies frequently.
*/
void GameScene::generateEnemies(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	float xMargin = SPACE_SHIP_WIDTH / 2.f;

	float occu_width = SPACE_SHIP_WIDTH * 3.f / 2.f;
	float occu_height = SPACE_SHIP_HEIGHT * 3.f / 2.f;
	float delta_val = visibleSize.width - xMargin * 2.f;
	int col_cnt = (int)(delta_val / occu_width + 1);
	int row_cnt = std::min(++m_level + 1, 5);
	m_level = row_cnt - 1;

	// arrange items in rows (2, 3, 4 and 5 rows of enemies, 5 is max)
	for (int j = 0; j < row_cnt; j++)
	{
		for (int i = 0; i < col_cnt; i++)
		{
			int nEnemyType = rand() % 2;
			// make random enemy ship
			SpriteBase* enemySprite = SpritePool::instance()->create(nEnemyType);
			if (enemySprite == nullptr) {
				printf("enemy ship creation failed.");
			}
			else {
				enemySprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				enemySprite->setPosition(Vec2(origin.x + xMargin + occu_width * i,
												visibleSize.height + origin.y + occu_height * j));
				this->addChild(enemySprite, 1);
			}
		}
	}
}

/**
* called every frame
*/
void GameScene::update(float dt)
{
	m_rocketReloadTimer += dt;
	if (m_rocketReloadTimer >= ROCKET_RELOAD_RATE)
	{
		m_rocketReloadTimer = 0.f;
		SpaceShip* spaceShip = (SpaceShip*)getChildByTag(TAG_SPACESHIP);

		// rocket is fired from spaceship
		Rocket* pRocket = spaceShip->fire();
		this->addChild(pRocket, 1);
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bool bEnemyExist = false;

	Vector<Node*> children = this->getChildren();
	Vector<Node*>::iterator myIterator;
	for (myIterator = children.begin(); myIterator != children.end(); ++myIterator)
	{
		auto child = *myIterator;
		// no update for other sprites.
		if (child->getTag() != TAG_SPACESHIP
					&& child->getTag() != TAG_ENEMY_SHIP 
					&& child->getTag() != TAG_ROCKET)
		{
			continue;
		}

		SpriteBase* agent = (SpriteBase*)child;
		if (agent->getTag() == TAG_ROCKET)
		{	// rocket move upwards
			agent->setPositionY(agent->getPositionY() + ROCKET_DELTA_Y);
			// If rocket has gone out of screen, remove from parent
			if (agent->getPositionY() > origin.y + visibleSize.height + 40.f) 
			{
				this->removeChild(agent);
				// push to pool for reuse
				SpritePool::instance()->push(agent);
			}
		}
		else if (agent->getTag() == TAG_SPACESHIP)
		{	// for self ship, if current is no touch state, continue
			if (!m_bTouchBegan)
			{
				continue;
			}
			float curx = agent->getPositionX();
			if (curx + SHIP_DELTA_X <= std::min(m_touchXPos, visibleSize.width - SPACE_SHIP_WIDTH / 2))
			{
				agent->setPositionX(curx + SHIP_DELTA_X);
			}
			else if (curx - SHIP_DELTA_X >= std::max(m_touchXPos, SPACE_SHIP_WIDTH / 2))
			{
				agent->setPositionX(curx - SHIP_DELTA_X);
			}
		}
		else if (agent->getTag() == TAG_ENEMY_SHIP)
		{
			// enemies are coming down.
			agent->setPositionY(agent->getPositionY() - SHIP_DELTA_Y);
			
			// If enemy ship has gone out of screen, remove from parent
			if (agent->getPositionY() < origin.y - SPACE_SHIP_HEIGHT)
			{
				this->removeChild(agent);
				agent->reset();
				SpritePool::instance()->push(agent);
			}
			else 
			{
				bEnemyExist = true;
			}
		}
	}

	// if no enemies, then generate new enemies
	if (!bEnemyExist)
	{
		generateEnemies();
	}
}
