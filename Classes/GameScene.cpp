#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	GameScene* gameScene = GameScene::create();
	//gameScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
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
		float y = origin.y + visibleSize.height - menuItem->getContentSize().height / 2;
		//menuItem->setGlobalZOrder(4);
		menuItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 3);

	// key listener
	keyListener = KeyListener::create(this->_eventDispatcher);

	// background
	level = Leveling::create();
	this->addChild(level, 1);

	player = Player::create();
	player->setPosition(Point((visibleSize.width / 2) + origin.x, 120));
	this->addChild(player, 2);

	//this->addChild(level, 1);
	/////////////////////////////
	// 3. add your codes below...

	return true;
}

void GameScene::goToMenu(Ref* Sender)
{
	Director::getInstance()->replaceScene(MainMenu::createScene());
}

void GameScene::keyCheck() {/*
	if (!keyListener->keyState[26] &&
		!keyListener->keyState[27] &&
		!keyListener->keyState[124] &&
		!keyListener->keyState[127]) {*/
	for (int _i = 0; _i < sizeof(keys) / sizeof(keys[0]); _i++) {
		if (keyListener->keyPressed[keys[_i]]) {
			player->stopAllActions();
			level->stopMoving();
			level->isMoving = false;
			keyListener->keyPressed[keys[_i]] = false;
		}
		if (keyListener->keyReleased[keys[_i]]) {
			player->stopAllActions();
			level->stopMoving();
			level->isMoving = false;
			keyListener->keyReleased[keys[_i]] = false;
		}
	}
	//}
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
	* SPACE			59
	*	1			77
	*	2			78
	*/
	if (player->state != State::isDead) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (player->state != State::isAttacking &&
			player->state != State::isTakingHit &&
			player->state != State::isDying) {
			keyCheck();
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
				if (player->state != State::isJumping) {
					player->state = State::isRunning;
				}
			}
			if (!keyState[26] && !keyState[27] &&
				!keyState[124] && !keyState[127]) {
				player->velocity = 0;
				if (player->state != State::isJumping) {
					player->state = player->stillState;
				}
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
		if (keyState[77]) {									// take hit
			if (player->state != State::isTakingHit) {
				player->stopAllActions();
				level->stopMoving();
				level->isMoving = false;
				player->velocity = 0;
				player->state = State::isTakingHit;
			}
		}
		if (keyState[78]) {									// die
			if (player->state != State::isDying) {
				player->stopAllActions();
				level->stopMoving();
				level->isMoving = false;
				player->velocity = 0;
				player->state = State::isDying;
			}
		}
		if (keyState[59]) {
			if (player->getPositionY() == 120) {
				player->YV = 15;
				player->state = State::isJumping;
			}
		}
	}
}

void GameScene::update(float dt) {
	whatKey(keyListener->keyState);
	player->update();
}

