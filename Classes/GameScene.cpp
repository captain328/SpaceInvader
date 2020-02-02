#include <stdlib.h>
#include "GameScene.h"
#include "GameOverScene.h"
#include "SpriteBase.h"
#include "SpriteFactory.h"
#include "Config.h"
#include "SpaceShip.h"
#include "Rocket.h"
#include "EnemyShip.h"

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

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "btn_close_normal.png",
                                           "btn_close_down.png",
                                           CC_CALLBACK_1(GameScene::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
		printf("'btn_close_normal.png' or 'btn_close_selected.png' is missing.");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

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
	SpaceShip* spaceShip = (SpaceShip*)SpriteFactory::instance()->create(TAG_SPACESHIP);
	if (spaceShip == nullptr) {
		printf("space ship creation failed.");
	}
	else {
		spaceShip->setPosition(Vec2(visibleSize.width / 2 + origin.x, SPACE_SHIP_HEIGHT * 3 + origin.y));
		this->addChild(spaceShip, 1);
	}
	
	m_bTouchBegan = false;
	m_killCntInNormal = 0;
	m_level = 0;
	m_elapsed = 0.f;
	m_rocketElapsed = 0.f;

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

bool GameScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
	m_bTouchBegan = true;
	m_touchXPos = touch->getLocation().x;
	return true;
}

bool GameScene::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
	m_touchXPos = touch->getLocation().x;
	return true;
}

bool GameScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
	m_bTouchBegan = false;
	return true;
}

// Handle collision event
bool GameScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
	// collision is made between two objects
	Node* shapeA = contact.getShapeA()->getBody()->getNode();
	Node* shapeB = contact.getShapeB()->getBody()->getNode();

	if ((shapeA->getTag() == TAG_ROCKET 
			&& shapeB->getTag() == TAG_ENEMY_SHIP)
		|| (shapeB->getTag() == TAG_ROCKET
			&& shapeA->getTag() == TAG_ENEMY_SHIP))
	{
		// rocket collide with enemy
		Rocket* pRocket = (Rocket*)(shapeA->getTag() == TAG_ROCKET ? shapeA : shapeB);
		EnemyShip* pEnemyShip = (EnemyShip*)(shapeA->getTag() == TAG_ENEMY_SHIP ? shapeA : shapeB);
		
		// force healthpoint reduction
		pEnemyShip->getHit(pRocket);
		if (pEnemyShip->isDead())
		{
			this->removeChild(pEnemyShip);
			SpriteFactory::instance()->push(pEnemyShip);
			increaseScore();
			m_killCntInNormal++;
		}
		this->removeChild(pRocket);
		SpriteFactory::instance()->push(pRocket);
	}
	else if (shapeA->getTag() == TAG_SPACESHIP
		|| shapeB->getTag() == TAG_SPACESHIP)
	{	// crashed
		this->stopAllActions();
		auto scene = GameOverScene::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(224, 30, 30)));
		return false;
	}
	return true;
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();
}

/**
* generate rockets frequently.
*/
void GameScene::generateRockets(float dt)
{
	auto rocketSprite = SpriteFactory::instance()->create(TAG_ROCKET);
	if (rocketSprite == nullptr) {
		printf("rocket creation failed.");
	}
	else {
		auto selfNode = getChildByTag(TAG_SPACESHIP);
		if (selfNode != nullptr)
		{
			rocketSprite->setPositionX(selfNode->getPositionX()); 
			rocketSprite->setPositionY(selfNode->getPositionY() + selfNode->getContentSize().height);
			this->addChild(rocketSprite, 1);
		}
	}
}

void GameScene::increaseScore()
{
	int curscore = std::atoi(m_scoreLabel->getString().c_str());
	curscore += 20;
	m_scoreLabel->setString(StringUtils::format("%d", curscore));
}

void GameScene::showCrashState()
{
	unscheduleUpdate();
	this->stopAllActions();

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto stateLabel = Label::createWithTTF("Game Over!", "fonts/arial.ttf", 32);
	if (stateLabel == nullptr)
	{
		printf("'fonts/arial.ttf' is missing.");
	}
	else
	{
		// position the label on the center of the screen
		stateLabel->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + (visibleSize.height - stateLabel->getContentSize().height) / 2));

		// add the label as a child to this layer
		this->addChild(stateLabel, 10);
	}


}

/**
* generate enemies frequently.
*/
void GameScene::generateEnemies(float dt)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

#define	SHIP_OCCU_WIDTH		SPACE_SHIP_WIDTH * 3.f / 2.f
#define	SHIP_OCCU_HEIGHT	SPACE_SHIP_HEIGHT * 3.f / 2.f
#define MARGIN_X			SPACE_SHIP_WIDTH / 2.f

	float occu_width = SHIP_OCCU_WIDTH;
	float delta_val = visibleSize.width - MARGIN_X * 2.f;
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
			auto enemySprite = SpriteFactory::instance()->create(nEnemyType);
			if (enemySprite == nullptr) {
				printf("enemy ship creation failed.");
			}
			else {
				enemySprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
				enemySprite->setPosition(Vec2(origin.x + MARGIN_X + SHIP_OCCU_WIDTH * i, 
												visibleSize.height + origin.y + SHIP_OCCU_HEIGHT * j));
				this->addChild(enemySprite, 1);
			}
		}
	}
}

/**
* Update function which is called every dt
*/
void GameScene::update(float dt)
{
	m_rocketElapsed += dt;
	if (m_rocketElapsed >= NORMAL_SPEED)
	{
		m_rocketElapsed = 0.f;
		generateRockets();
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	bool bEnemyExist = false;

	cocos2d::Vector<Node*> children = this->getChildren();
	for each (Node* child in children)
	{
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
				SpriteFactory::instance()->push(agent);
			}
		}
		else if (agent->getTag() == TAG_SPACESHIP)
		{	// for self ship, if current is no touch state, continue
			if (!m_bTouchBegan)
			{
				continue;
			}
			float curx = agent->getPositionX();
			if (curx + SHIP_DELTA_X <= m_touchXPos)
			{
				agent->setPositionX(curx + SHIP_DELTA_X);
			}
			else if (curx - SHIP_DELTA_X >= m_touchXPos)
			{
				agent->setPositionX(curx - SHIP_DELTA_X);
			}
		}
		else if (agent->getTag() == TAG_ENEMY_SHIP)
		{	// enemies are coming down.
			agent->setPositionY(agent->getPositionY() - SHIP_DELTA_Y);
			// If enemy ship has gone out of screen, remove from parent
			if (agent->getPositionY() < origin.y - SPACE_SHIP_HEIGHT)
			{
				this->removeChild(agent);
				SpriteFactory::instance()->push(agent);
			}
			else 
			{
				bEnemyExist = true;
			}
		}
	}

	// if no enemies, then to appear enemies
	if (!bEnemyExist)
	{
		generateEnemies();
	}
}

