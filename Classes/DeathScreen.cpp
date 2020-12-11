#include "DeathScreen.h"
#include "MainMenu.h"
#include <ui/CocosGUI.h>

USING_NS_CC;

Scene* DeathScreen::createScene() {
	auto scene = Scene::create();

	auto layer = DeathScreen::create();

	//layer->setGlobalZOrder(4);

	scene->addChild(layer);

	return scene;
}

bool DeathScreen::init() {

	if (!Scene::init()) {
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	//this->scheduleOnce(CC_SCHEDULE_SELECTOR(DeathScreen::GoToMainMenu), 2);

	auto backgroundSprite = Sprite::create("lya1.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

	this->addChild(backgroundSprite);

	return true;
}

void DeathScreen::GoToMainMenu(float dt)
{
	/*auto scene = MainMenu::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));*/
	Director::getInstance()->replaceScene(MainMenu::createScene());
}

void DeathScreen::onEnter() {

	Scene::onEnter();

	this->scheduleOnce(CC_SCHEDULE_SELECTOR(DeathScreen::GoToMainMenu), 2.0f);
}
