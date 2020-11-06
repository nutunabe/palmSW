#include "GameScene.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	return GameScene::create();
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Scene::init())
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto menuItem = MenuItemImage::create(
        "Menu Button.png",
        "Menu Button Clicked.png",
        CC_CALLBACK_1(GameScene::goToMenu, this));

    if (menuItem == nullptr ||
        menuItem->getContentSize().width <= 0 ||
        menuItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - menuItem->getContentSize().width / 2;
        float y = origin.y + menuItem->getContentSize().height / 2;
        menuItem->setPosition(Vec2(x, y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(menuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    mySprite = Sprite::create("HelloSaddam.png");

    mySprite->setPosition(Point((visibleSize.width / 2) + origin.x, (visibleSize.height / 2) + origin.y));
     
    this->addChild(mySprite);

    auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [](EventKeyboard::KeyCode keyCode, Event* event) {
        Vec2 loc = event->getCurrentTarget()->getPosition();
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
        case EventKeyboard::KeyCode::KEY_A:
            event->getCurrentTarget()->setPosition(loc.x = loc.x - 50, loc.y);
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
        case EventKeyboard::KeyCode::KEY_D:
            event->getCurrentTarget()->setPosition(loc.x = loc.x + 50, loc.y);
            break;
        }
    };
    this->_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, mySprite);

    return true;
}


void GameScene::goToMenu(Ref* Sender) 
{
    Director::getInstance()->replaceScene(MainMenu::createScene());
}