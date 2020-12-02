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
	player->minGroundY = groundLevel;
	player->setPosition(Point((visibleSize.width / 2) + origin.x, player->minGroundY));
	this->addChild(player, 4);

	platforms[0] = Platform::create(200, 150, 200, 50);
	platforms[1] = Platform::create(800, 150, 200, 50);
	platforms[2] = Platform::create(450, 200, 200, 50);
	platforms[3] = Platform::create(200, 260, 200, 50);
	platforms[4] = Platform::create(550, 300, 200, 50);
	platforms[5] = Platform::create(650, 400, 200, 50);

	for (int i = 0; i < (sizeof(platforms) / sizeof(*platforms)); i++) {
		this->addChild(platforms[i], 2);
	}

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
	* arrow up		28-
	* arrow left	26
	* arrow down	29-
	* arrow right	27
	*	W			146-
	*	A			124
	*	S			142-
	*	D			127
	*	F			129
	* SPACE			59
	*	1			77
	*	2			78
	*/
	if (player->state != State::isDead &&
		player->state != State::isDying) {
		Size visibleSize = Director::getInstance()->getVisibleSize();
		if (player->state != State::isAttacking &&
			player->state != State::isTakingHit) {
			keyCheck();
			if (keyState[26] || keyState[124] || keyState[27] || keyState[127]) {
				if (keyState[26] || keyState[124]) {		// left
					level->setDirectionLeft();
					if (player->getPositionX() < visibleSize.width / 6) {
						player->velocityX = 0;
						if (level->isMoving == false) {
							level->parallax();
							level->isMoving = true;
						}
					}
					else {
						player->velocityX = -1 * player->velocityMax;
						player->setScaleX(abs(player->getScaleX()));
					}
				}
				else if (keyState[27] || keyState[127]) {	// right
					level->setDirectionRight();
					if (player->getPositionX() > visibleSize.width - visibleSize.width / 6) {
						player->velocityX = 0;
						if (level->isMoving == false) {
							level->parallax();
							level->isMoving = true;
						}
					}
					else {
						player->velocityX = player->velocityMax;
						player->setScaleX(abs(player->getScaleX()) * -1);
					}
				}
				if (player->state != State::isJumping) {
					player->state = State::isRunning;
				}
			}
			if (!keyState[26] && !keyState[27] &&
				!keyState[124] && !keyState[127]) {
				player->velocityX = 0;
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
				player->velocityX = 0;
				player->state = State::isAttacking;
			}
		}
		if (keyState[77]) {									// take hit
			if (player->state != State::isTakingHit) {
				player->stopAllActions();
				level->stopMoving();
				level->isMoving = false;
				player->velocityX = 0;
				player->state = State::isTakingHit;
			}
		}
		if (keyState[78]) {									// die
			if (player->state != State::isDying) {
				player->stopAllActions();
				level->stopMoving();
				level->isMoving = false;
				player->velocityX = 0;
				player->state = State::isDying;
			}
		}
		if (keyState[59]) {									// jump
			if (player->getPositionY() == player->minGroundY) {
				player->velocityY = 15;
				player->state = State::isJumping;
			}
		}
	}
}

void GameScene::checkActivePlatform() {
	int maxY = -1;
	for (int i = 0; i < (sizeof(platforms) / sizeof(*platforms)); i++) {
		if (player->getPositionX() > platforms[i]->coordinate.x && player->getPositionX() < platforms[i]->coordinate.x + platforms[i]->size.width) {
			if (player->getPositionY() >= platforms[i]->coordinate.y) {
				if (platforms[i]->coordinate.y > maxY) {
					maxY = platforms[i]->coordinate.y;
					activePlatform = platforms[i];
				}
			}
		}
	}

	if (maxY == -1) {
		player->minGroundY = groundLevel;
	}
	else {
		player->minGroundY = activePlatform->coordinate.y;
	}
}

void GameScene::update(float dt) {
	whatKey(keyListener->keyState);

	player->update();

	checkActivePlatform();
}

