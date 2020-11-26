#include "MainMenu.h"
#include "GameScene.h"
#include <ui/CocosGUI.h>

USING_NS_CC;

Scene* MainMenu::createScene() {
	auto scene = Scene::create();

	auto layer = MainMenu::create();

    layer->setGlobalZOrder(4);

	scene->addChild(layer);

	return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

bool MainMenu::init() {
	
	if ( !Layer::init()) {
		return false;
	}

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto backgroundSprite = Sprite::create("Background.png");
    backgroundSprite->setContentSize(visibleSize);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);


    auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(MainMenu::GoToGameScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto menu = Menu::create(playItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);


    return true;
}

void MainMenu::GoToGameScene(Ref* sender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());

    /*auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));*/
}

void MainMenu::menuCloseCallback(Ref* sender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}