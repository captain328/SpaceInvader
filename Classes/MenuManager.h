#pragma once
#include "cocos2d.h"

class MenuManager
{
private:
	static MenuManager* _instance;
public:
	MenuManager();
	static MenuManager* instance();
	void switchScene(int nScene);
	void quit();
};

