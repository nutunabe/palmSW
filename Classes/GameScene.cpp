#include "GameScene.h"
#include "MainMenu.h"
#include "Player.h"
#include "Leveling.h"
#include "KeyListener.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	GameScene* gameScene = GameScene::create();
	gameScene->scheduleUpdate();
	return gameScene;
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
    this->addChild(menu, 3);

    // key listener
    keyListener = KeyListener::create(this->_eventDispatcher);
   
	// background
	player = Player::create();
	player->setPosition(Point((visibleSize.width / 2) + origin.x, 130));
	this->addChild(player, 2);

	level = Leveling::create();
	this->addChild(level, 1);
    /////////////////////////////
    // 3. add your codes below...

    return true;
}

void GameScene::goToMenu(Ref* Sender) 
{
    Director::getInstance()->replaceScene(MainMenu::createScene());
}

void GameScene::whatKey(bool* keyState) {
	/*
	* arrow up		28
	* arrow left	26
	* arrow down	29
	* arrow right	27
	*	W			146
	*	A			124
	*	S			142
	*	D			127
	*	F			129
	*/
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (player->state != State::isAttacking) {
		if (keyListener->keyPressed) {
			CCLOG("PRESSED");
			player->stopAllActions();
			keyListener->keyPressed = false;
			level->stopMoving();
			level->isMoving = false;
		}
		if (keyListener->keyReleased) {
			CCLOG("RELEASED");
			player->stopAllActions();
			keyListener->keyReleased = false;
			level->stopMoving();
			level->isMoving = false;
		}
		if (keyState[26] || keyState[124] || keyState[27] || keyState[127]) {
			if (keyState[26] || keyState[124]) {		// left
				level->setDirectionLeft();
				if (player->getPositionX() < visibleSize.width / 6) {
					player->velocity = 0;
					if (level->isMoving == false) {
						level->parallax();
						level->isMoving = true;
					}
				}
				else {
					player->velocity = -1 * player->maxVelocity;
					player->setScaleX(abs(player->getScaleX()));
				}
			}
			else if (keyState[27] || keyState[127]) {	// right
				level->setDirectionRight();
				if (player->getPositionX() > visibleSize.width - visibleSize.width / 6) {
					player->velocity = 0;
					if (level->isMoving == false) {
						level->parallax();
						level->isMoving = true;
					}
				}
				else {
					player->velocity = player->maxVelocity;
					player->setScaleX(abs(player->getScaleX()) * -1);
				}
			}
			player->state = State::isRunning;
		}
		if (!keyState[26] && !keyState[27] &&
			!keyState[124] && !keyState[127]) {
			player->velocity = 0;
			player->state = State::isReady;
		}
	}
	if (keyState[129]) {								// attack
		if (player->state != State::isAttacking) {
			level->stopMoving();
			level->isMoving = false;
			player->stopAllActions();
			player->velocity = 0;
			player->state = State::isAttacking;
		}
	}
}

void GameScene::update(float dt) {
	whatKey(keyListener->keyState);
	player->update();
}

