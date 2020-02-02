#include "MenuManager.h"
#include "Config.h"
#include "GameOverScene.h"
#include "GameScene.h"

USING_NS_CC;

MenuManager* MenuManager::_instance = nullptr;

MenuManager* MenuManager::instance() {
	if (_instance == nullptr) {
		_instance = new MenuManager();
	}
	return _instance;
}

MenuManager::MenuManager()
{
	// nothing to do here
}

void MenuManager::switchScene(int nScene)
{
	switch (nScene)
	{
		case SCENE_GAME_OVER:
		{
			auto scene = GameOverScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(224, 30, 30)));
			break;
		}
		case SCENE_GAME_PLAY:
		{
			auto scene = GameScene::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene, Color3B(224, 30, 30)));
			break;
		}
		default:
			return;
	}
}

void MenuManager::quit()
{
	Director::getInstance()->end();
}
