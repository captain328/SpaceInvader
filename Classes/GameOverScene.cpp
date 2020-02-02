
#include "GameOverScene.h"
#include "GameScene.h"
#include "MenuManager.h"
#include "config.h"
USING_NS_CC;

Scene* GameOverScene::createScene()
{
	return GameOverScene::create();
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    // super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto retryItem = MenuItemImage::create(
										"btn_retry_normal.png",
										"btn_retry_down.png",
										CC_CALLBACK_1(GameOverScene::menuRetryCallback, this));

	if (retryItem == nullptr ||
		retryItem->getContentSize().width <= 0 ||
		retryItem->getContentSize().height <= 0)
	{
		printf("'btn_retry_normal.png' or 'btn_retry_down.png' is missing.");
	}
	else
	{
		retryItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_RIGHT);
		float x = origin.x + visibleSize.width / 2 - 30.f;
		float y = origin.y + retryItem->getContentSize().height * 2;
		retryItem->setPosition(Vec2(x, y));
	}

    auto exitItem = MenuItemImage::create(
                                           "btn_exit_normal.png",
                                           "btn_exit_down.png",
                                           CC_CALLBACK_1(GameOverScene::menuExitCallback, this));

    if (exitItem == nullptr ||
        exitItem->getContentSize().width <= 0 ||
        exitItem->getContentSize().height <= 0)
    {
		printf("'btn_exit_normal.png' or 'btn_exit_down.png' is missing.");
    }
    else
    {
		exitItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
        float x = origin.x + visibleSize.width / 2 + 30.f;
        float y = origin.y + exitItem->getContentSize().height * 2;
        exitItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(exitItem, retryItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 10);

    // add a label shows game title
    // create and initialize a label

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

    // add background
    auto sprite = Sprite::create("background.png");
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

    return true;
}

void GameOverScene::menuExitCallback(Ref* pSender)
{
	MenuManager::instance()->quit();
}

void GameOverScene::menuRetryCallback(Ref* pSender)
{
	MenuManager::instance()->switchScene(SCENE_GAME_PLAY);
}
