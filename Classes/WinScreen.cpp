#include "WinScreen.h"
#include "MainMenu.h"
#include <ui/CocosGUI.h>

USING_NS_CC;

Scene* WinScreen::createScene() {
	auto scene = Scene::create();

	auto layer = WinScreen::create();

	scene->addChild(layer);

	return scene;
}

bool WinScreen::init() {

	if (!Scene::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto backgroundSprite = Sprite::create("WinScreen2.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	return true;
}

void WinScreen::GoToMainMenu(float dt)
{
	Director::getInstance()->replaceScene(MainMenu::createScene());
}

void WinScreen::onEnter() {

	Scene::onEnter();

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(WinScreen::GoToMainMenu), 5.0f);
}

