#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	GameScene* gameScene = GameScene::create();
	//gameScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	//gameScene->init();
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

	goblin = Goblin::create();
	goblin->minGroundY = groundLevel-10;
	goblin->setPosition(Point((visibleSize.width * 0.7) + origin.x, goblin->minGroundY - 150));
	this->addChild(goblin, 3);

	enemyLogic = new EnemyLogic(goblin, player, groundLevel);

	platforms[0] = Platform::create(200, 150, 200, 50);
	platforms[1] = Platform::create(800, 150, 200, 50);
	platforms[2] = Platform::create(450, 200, 200, 50);
	platforms[3] = Platform::create(200, 260, 200, 50);
	platforms[4] = Platform::create(550, 300, 200, 50);
	platforms[5] = Platform::create(650, 400, 200, 50);

	for (int i = 0; i < (sizeof(platforms) / sizeof(*platforms)); i++) {
		this->addChild(platforms[i], 2);
	}

	hud = HUD::create();
	this->addChild(hud, 5);

	coin = Coin::create(750, 150, 40, 20);
	this->addChild(coin, 2);

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
			for (auto plat : platforms) {
				plat->stopAllActions();
			}
			keyListener->keyPressed[keys[_i]] = false;
		}
		if (keyListener->keyReleased[keys[_i]]) {
			player->stopAllActions();
			level->stopMoving();
			level->isMoving = false;
			for (auto plat : platforms) {
				plat->stopAllActions();
			}
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
							for (auto plat : platforms) {
								plat->setDirectionLeft();
								plat->parallax();
							}
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
							for (auto plat : platforms) {
								plat->setDirectionRight();
								plat->parallax();
							}
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
				for (auto plat : platforms) {
					plat->stopAllActions();
				}
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
				for (auto plat : platforms) {
					plat->stopAllActions();
				}
				player->velocityX = 0;
				player->state = State::isTakingHit;
				hud->getHit(10, player);
			}
		}
		if (keyState[78]) {									// die
			if (player->state != State::isDying) {
				player->stopAllActions();
				level->stopMoving();
				for (auto plat : platforms) {
					plat->stopAllActions();
				}
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
		if (player->getPositionX() > platforms[i]->getPositionX() && player->getPositionX() < platforms[i]->getPositionX() + platforms[i]->size.width) {
			if (player->getPositionY() >= platforms[i]->getPositionY()) {
				if (platforms[i]->getPositionY() > maxY) {
					maxY = platforms[i]->getPositionY();
					activePlatform = platforms[i];
				}
			}
		}
	}

	if (maxY == -1) {
		player->minGroundY = groundLevel;
	}
	else {
		player->minGroundY = activePlatform->getPositionY();
	}
}

void GameScene::checkTakeCoin() {
	if (coin->exist == true&&
		player->getPositionX() + player->getContentSize().width / 2 >= coin->coordinate.x &&
		player->getPositionX() - player->getContentSize().width / 2 <= coin->coordinate.x &&
		player->getPositionY() + player->getContentSize().height + 70 >= coin->coordinate.y &&
		player->getPositionY() - player->getContentSize().height <= coin->coordinate.y 
		)
	{
		coin->exist = false;
		hud->count += 1;
		hud->update();
		removeChild(coin, false);
	}
}

void GameScene::update(float dt) {
	whatKey(keyListener->keyState);

	enemyLogic->chasePlayer();

	player->update();
	goblin->update();

	checkActivePlatform();
	
	checkTakeCoin();
}

/*void GameScene::pause(Ref* Sender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume();
	}
	else {
		Director::getInstance()->pause();
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
			float x = origin.x + visibleSize.width / 2 - menuItem->getContentSize().width / 2;
			float y = origin.y + visibleSize.height / 2 - menuItem->getContentSize().height / 2;
			menuItem->setPosition(Vec2(x, y));
		}
		auto menu = Menu::create(menuItem, NULL);
		menu->setPosition(Vec2::ZERO);
		this->addChild(menu, 3);
	}
}*/
