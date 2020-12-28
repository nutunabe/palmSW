#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene() {
	GameScene* gameScene = GameScene::create();
	gameScene->scheduleUpdate();
	//gameScene->listenKeyboard();
	return gameScene;
}

static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	/*auto menuItem = MenuItemImage::create(
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
		menuItem->setPosition(Vec2(x, y));
	}*/



	/*auto pauseLabel = Label::createWithTTF("Pause", FONT_DEFINITION, 24);
	auto pauseItem = MenuItemLabel::create(pauseLabel, CC_CALLBACK_1(GameScene::pause, this));
	pauseItem->setPosition(
		Vec2(origin.x + visibleSize.width - pauseItem->getContentSize().width / 2,
			origin.y + visibleSize.height - pauseItem->getContentSize().height / 2)
	);*/

	// create menu, it's an autorelease object

	/*auto Shoplabel = Label::createWithTTF("Press ME", FONT_DEFINITION, 24);
	auto shop1 = MenuItemLabel::create(Shoplabel, CC_CALLBACK_1(GameScene::checkShop, this));
	shop1->setPosition(Point(1000, 350));*/
	//hud->addChild(shop1, 2);

	keyListener = KeyListener::create(this->_eventDispatcher);

	initCharacters();

	/*auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2::ZERO);

	hud = HUD::create(player);
	hud->addChild(menu);
	this->addChild(hud, 5);*/

	for (int i = 0; i <= 2; i++) {
		auto coin = Coin::create(1150 + i * 50, 300, 35, 35);
		this->addChild(coin, 2);
		coins.pushBack(coin);
	}
	for (int i = 0; i <= 4; i++) {
		auto coin = Coin::create(2600 + i * 50, 400, 35, 35);
		this->addChild(coin, 2);
		coins.pushBack(coin);
	}
	for (int i = 0; i <= 3; i++) {
		auto coin = Coin::create(4525 + i * 50, 400, 35, 35);
		this->addChild(coin, 2);
		coins.pushBack(coin);
	}

	shop = Shop::create(3500, 200, 280, 280);
	this->addChild(shop, 1);

	return true;
}

void GameScene::initEnvironment() {
	// background
	level = Leveling::create();
	this->addChild(level, 1);
	level->setPositionX(player->getPositionX() - Director::getInstance()->getWinSize().width);

	auto platform = Platform::create(800, 125, 200, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(1200, 205, 500, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(1600, 125, 200, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);

	platform = Platform::create(2200, 123, 400, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(2800, 121, 400, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(2300, 200, 100, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(2100, 270, 100, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(2250, 370, 250, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(2700, 300, 300, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);

	platform = Platform::create(4000, 127, 300, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(4300, 207, 300, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(4600, 302, 300, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(4900, 203, 300, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	platform = Platform::create(5200, 119, 300, 50);
	this->addChild(platform, 2);
	platforms.pushBack(platform);
	/*platforms[1] = Platform::create(800, 125, 200, 50);
	platforms[2] = Platform::create(450, 175, 200, 50);
	platforms[3] = Platform::create(200, 235, 200, 50);
	platforms[4] = Platform::create(550, 275, 200, 50);
	platforms[5] = Platform::create(650, 375, 200, 50);*/

		//=========================================//
		//Color4F white(1, 1, 1, 1);
		//Color4F red(.7, 0, 0, 1);
		//Color4F green(0, .7, 0, 1);
		//Color4F yellow(.7, .7, 0, 1);
		//auto platformNode = DrawNode::create();
		//int xi = platforms[i]->getLeft();
		//int yi = platforms[i]->getTop();
		//int xd = platforms[i]->getRight();
		//int yd = platforms[i]->getBottom();
		//platformNode->drawRect(Point(xi, yi), Point(xd, yd), white);
		//platformNode->drawDot(platforms[i]->getPosition(), 3.f, red);
		//this->addChild(platformNode, 40);
		//=========================================//
	// . . .
}

void GameScene::initCharacters() {
	player = Player::create();
	player->minGroundY = groundLevel;
	player->setPosition(Point((visibleSize.width / 2) + origin.x, player->minGroundY - player->getBottom()));
	this->addChild(player, 4);

	initEnvironment();

	//=========================================//
	auto pauseLabel = Label::createWithTTF("Pause", FONT_DEFINITION, 24);
	auto pauseItem = MenuItemLabel::create(pauseLabel, CC_CALLBACK_1(GameScene::pause, this));
	pauseItem->setPosition(
		Vec2(origin.x + visibleSize.width - pauseItem->getContentSize().width / 2,
			origin.y + visibleSize.height - pauseItem->getContentSize().height / 2)
	);

	auto menu = Menu::create(pauseItem, NULL);
	menu->setPosition(Vec2::ZERO);

	hud = HUD::create(player);
	hud->addChild(menu);
	this->addChild(hud, 5);
	//=========================================//
	//Color4F white(1, 1, 1, 1);
	//Color4F red(.7, 0, 0, 1);
	//Color4F green(0, .7, 0, 1);
	//Color4F yellow(.7, .7, 0, 1);
	//groundNode = DrawNode::create();
	//groundNode->drawLine(Point(0.f, groundLevel), Point(visibleSize.width, groundLevel), green);
	//this->addChild(groundNode, 1);
	//playerNode = DrawNode::create();
	//int xi = player->getLeft();
	//int yi = player->getTop();
	//int xd = player->getRight();
	//int yd = player->getBottom();
	//playerNode->drawRect(Point(xi, yi), Point(xd, yd), white);
	//playerNode->drawDot(player->getPosition(), 3.f, red);
	//this->addChild(playerNode, 4);
	//=========================================//
	initEnemies();
}

void GameScene::initEnemies() {
	auto goblin = Goblin::create();
	goblin->minGroundY = groundLevel;
	goblin->setPosition(Point((visibleSize.width * 0.7) + origin.x, goblin->minGroundY - goblin->getBottom()));
	goblin->setName("goblin");
	this->addChild(goblin, 3);
	goblins.pushBack(goblin);

	goblin = Goblin::create();
	goblin->minGroundY = platforms.at(1)->getTop();
	goblin->setPosition(Point(1200, goblin->minGroundY - goblin->getBottom()));
	goblin->setName("goblin");
	this->addChild(goblin, 3);
	goblins.pushBack(goblin);

	goblin = Goblin::create();
	goblin->minGroundY = platforms.at(3)->getTop();
	goblin->setPosition(Point(2200, goblin->minGroundY - goblin->getBottom()));
	goblin->setName("goblin");
	this->addChild(goblin, 3);
	goblins.pushBack(goblin);

	goblin = Goblin::create();
	goblin->minGroundY = platforms.at(4)->getTop();
	goblin->setPosition(Point(2700, goblin->minGroundY - goblin->getBottom()));
	goblin->setName("goblin");
	this->addChild(goblin, 3);
	goblins.pushBack(goblin);
	//=========================================//
	//Color4F red(.7, 0, 0, 1);
	//Color4F yellow(.7, .7, 0, 1);
	//auto goblinNode = DrawNode::create();
	//goblinNode->drawRect(Point(goblin->getLeft(), goblin->getTop()), Point(goblin->getRight(), goblin->getBottom()), yellow);
	//goblinNode->drawDot(goblin->getPosition(), 3.f, red);
	//this->addChild(goblinNode, 3);
	//=========================================//
	//enemyLogic = new EnemyLogic(goblins, player, groundLevel, hud);
	
	auto skeleton = Skeleton::create();
	skeleton->minGroundY = groundLevel;
	skeleton->setPosition(Point(1500 , skeleton->minGroundY - skeleton->getBottom()));
	this->addChild(skeleton, 3);
	skeletons.pushBack(skeleton);

	skeleton = Skeleton::create();
	skeleton->minGroundY = platforms.at(8)->getTop();
	skeleton->setPosition(Point(2700, skeleton->minGroundY - skeleton->getBottom()));
	this->addChild(skeleton, 3);
	skeletons.pushBack(skeleton);

	skeleton = Skeleton::create();
	skeleton->minGroundY = platforms.at(10)->getTop();
	skeleton->setPosition(Point(4300, skeleton->minGroundY - skeleton->getBottom()));
	this->addChild(skeleton, 3);
	skeletons.pushBack(skeleton);

	skeleton = Skeleton::create();
	skeleton->minGroundY = platforms.at(11)->getTop();
	skeleton->setPosition(Point(4600, skeleton->minGroundY - skeleton->getBottom()));
	this->addChild(skeleton, 3);
	skeletons.pushBack(skeleton);

	skeleton = Skeleton::create();
	skeleton->minGroundY = platforms.at(12)->getTop();
	skeleton->setPosition(Point(4900, skeleton->minGroundY - skeleton->getBottom()));
	this->addChild(skeleton, 3);
	skeletons.pushBack(skeleton);
	//========================================//
	/*Color4F red(.7, 0, 0, 1);
	Color4F yellow(.7, .7, 0, 1);
	auto skeletonNode = DrawNode::create();
	skeletonNode->drawRect(Point(skeleton->getLeft(), skeleton->getTop()), Point(skeleton->getRight(), skeleton->getBottom()), yellow);
	skeletonNode->drawDot(skeleton->getPosition(), 3.f, red);
	this->addChild(skeletonNode, 3);*/
	//========================================//	if (goblin->state = State::isDead) {
	skeletonLogic = new SkeletonLogic(skeletons, player, groundLevel, hud);
	enemyLogic = new EnemyLogic(goblins, player, groundLevel, hud);

	boss = Boss::create();
	boss->minGroundY = groundLevel;
	boss->setPosition(Point(6700, boss->minGroundY - boss->getBottom()));
	this->addChild(boss, 3);

	for (int i = 0; i < 7; i++) {
		auto bp = BossProjectile::create();
		bp->setPosition(Point(0, 800));
		bossproj.pushBack(bp);
		this->addChild(bp, 5);
	}

	/*Color4F red(.7, 0, 0, 1);
	Color4F yellow(.7, .7, 0, 1);
	bossNode = DrawNode::create();
	bossNode->drawRect(Point(boss->getLeft(), boss->getTop()), Point(boss->getRight(), boss->getBottom()), yellow);
	bossNode->drawDot(boss->getPosition(), 3.f, red);
	bossNode->setName("bossNode");
	this->addChild(bossNode, 3);*/

	bossLogic = new BossLogic(boss, player, hud, bossproj);
}

void GameScene::goToMenu(Ref* Sender)
{
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume();
		Director::getInstance()->replaceScene(MainMenu::createScene());
	}
	else {
		Director::getInstance()->replaceScene(MainMenu::createScene());
	}
}

void GameScene::keyCheck() {
	for (int _i = 0; _i < sizeof(keys) / sizeof(keys[0]); _i++) {
		if (keyListener->keyPressed[keys[_i]]) {
			player->stopAllActions();
			level->stopMoving();
			level->flag = false;
			keyListener->keyPressed[keys[_i]] = false;
		}
		if (keyListener->keyReleased[keys[_i]]) {
			player->stopAllActions();
			level->stopMoving();
			level->flag = false;
			keyListener->keyReleased[keys[_i]] = false;
		}
	}
	//for (int _i = 0; _i < sizeof(keys) / sizeof(keys[0]); _i++) {
	//	if (keyPressed[keys[_i]]) {
	//		player->stopAllActions();
	//		level->stopMoving();
	//		level->flag = false;
	//		keyPressed[keys[_i]] = false;
	//	}
	//	if (keyReleased[keys[_i]]) {
	//		player->stopAllActions();
	//		level->stopMoving();
	//		level->flag = false;
	//		keyReleased[keys[_i]] = false;
	//	}
	//}
}

void GameScene::whatKey(bool* keyState) {
	/*
	* arrow left	26
	* arrow right	27
	*	A			124
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
			if ((keyState[26] || keyState[124] || keyState[27] || keyState[127])) {

				//player->setPositionX(player->getPositionX() + player->velocityX);

				if (keyState[26] || keyState[124]) {		// left
					if (player->getPositionX() <= levelLeftEdge + visibleSize.width / 2 || player->getPositionX() >= levelRightEdge - visibleSize.width / 2) {
						level->stopMoving();
						level->flag = false;
						if (player->getPositionX() <= levelLeftEdge + visibleSize.width / 2) {
							auto cam = Camera::getDefaultCamera();
							cam->setPositionX(levelLeftEdge + visibleSize.width / 2);
							hud->setPositionX(levelLeftEdge - origin.x);
						}
						if (player->getPositionX() >= levelRightEdge - visibleSize.width / 2) {
							auto cam = Camera::getDefaultCamera();
							cam->setPositionX(levelRightEdge - visibleSize.width / 2);
							hud->setPositionX(levelRightEdge - origin.x - visibleSize.width);
						}
					}
					else {
						level->setDirectionLeft();
						level->parallax();
						level->flag = true;
						auto cam = Camera::getDefaultCamera();
						cam->setPositionX(player->getPositionX());
						level->setPositionX(player->getPositionX() - Director::getInstance()->getWinSize().width);
						hud->setPositionX(player->getPositionX() - origin.x - visibleSize.width / 2);
					}

					player->setScaleX(abs(player->getScaleX()));

					if (player->getLeft() <= levelLeftEdge) {
						player->velocityX = 0;
					}
					else {
						player->velocityX = -1 * player->getVelocityMax();
					}
				}
				else if (keyState[27] || keyState[127]) {	// right
					if (player->getPositionX() <= levelLeftEdge + visibleSize.width / 2 || player->getPositionX() >= levelRightEdge - visibleSize.width / 2) {
						level->stopMoving();
						level->flag = false;
						if (player->getPositionX() <= levelLeftEdge + visibleSize.width / 2) {
							auto cam = Camera::getDefaultCamera();
							cam->setPositionX(levelLeftEdge + visibleSize.width / 2);
							hud->setPositionX(levelLeftEdge - origin.x);
						}
						if (player->getPositionX() >= levelRightEdge - visibleSize.width / 2) {
							auto cam = Camera::getDefaultCamera();
							cam->setPositionX(levelRightEdge - visibleSize.width / 2);
							hud->setPositionX(levelRightEdge - origin.x - visibleSize.width);
						}
					}
					else {
						level->setDirectionRight();
						level->parallax();
						level->flag = true;
						auto cam = Camera::getDefaultCamera();
						cam->setPositionX(player->getPositionX());
						level->setPositionX(player->getPositionX() - Director::getInstance()->getWinSize().width);
						hud->setPositionX(player->getPositionX() - origin.x - visibleSize.width / 2);
					}

					player->setScaleX(abs(player->getScaleX()) * -1);

					if (player->getRight() >= levelRightEdge) {
						player->velocityX = 0;
					}
					else {
						player->velocityX = player->getVelocityMax();
					}
				}
				if (player->state != State::isJumping) {
					player->state = State::isRunning;
					//player->update();
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
			if (player->getStamina() >= 5) {
				if (player->state != State::isAttacking) {
					level->stopMoving();
					level->flag = false;
					player->stopAllActions();
					player->velocityX = 0;
					player->state = State::isAttacking;
					player->setStamina(-5);
				}
			}
		}
		//if (keyState[77]) {									// take hit
		//	if (player->state != State::isTakingHit) {
		//		player->stopAllActions();
		//		level->stopMoving();
		//		level->flag = false;
		//		player->velocityX = 0;
		//		player->state = State::isTakingHit;
		//		hud->getHit(10, player);
		//	}
		//}
		//if (keyState[78]) {									// die
		//	if (player->state != State::isDying) {
		//		player->stopAllActions();
		//		level->stopMoving();
		//		level->flag = false;
		//		player->velocityX = 0;
		//		player->state = State::isDying;
		//	}
		//}
		if (keyState[59]) {								   // jump
			if (player->getStamina() >= 10) {
				if (player->getBottom() == player->minGroundY) {
					player->velocityY = 15;
					player->state = State::isJumping;
					player->setStamina(-10);
				}
			}
		}
	}
}

void GameScene::checkActivePlatform() {
	int maxY = -1;
	for (auto p: platforms) {
		if (player->getRight() - player->getWidth() / 4 > p->getLeft() && player->getLeft() + player->getWidth() / 4 < p->getRight()) {
			if (player->getBottom() >= p->getTop()) {
				if (p->getTop() > maxY) {
					maxY = p->getTop();
					activePlatform = p;
				}
			}
		}
	}

	if (maxY == -1) {
		player->minGroundY = groundLevel;
	}
	else {
		player->minGroundY = activePlatform->getTop();
	}
}

void GameScene::shopButton() {
	if (player->getRight() >= shop->getPositionX() &&
		player->getLeft() <= shop->getPositionX() &&
		player->getTop() >= shop->getPositionY() - 150 &&
		player->getBottom() <= shop->getPositionY())
	{
		if (check == false) {
			auto Shoplabel = Label::createWithTTF("Press ME", FONT_DEFINITION, 24);
			auto shop1 = MenuItemLabel::create(Shoplabel, CC_CALLBACK_1(GameScene::checkShop, this));
			shop1->setPosition(shop->getPosition());
			auto menu = Menu::create(shop1, NULL);
			menu->setName("menu");
			menu->setPosition(Vec2::ZERO);
			this->addChild(menu, 10);
			check = true;
		}
	}
	else
	{
		check = false;
	}
}


void GameScene::checkTakeCoin() {
	for (auto coin : coins) {
		if (coin->exist == true &&
			player->getRight() - player->getWidth() / 5 >= coin->getPositionX() &&
			player->getLeft() + player->getWidth() / 5 <= coin->getPositionX() &&
			player->getTop() >= coin->getPositionY() &&
			player->getBottom() <= coin->getPositionY()
			)
		{
			coin->exist = false;
			hud->count += 1;
			hud->update();
			removeChild(coin, false);
		}
	}
}

void GameScene::checkShop(Ref* sender) {
	UICustom::Popup* popup = UICustom::Popup::createAsConfirmDialogue("MAGAZZZ", "rnd Health = 1 coin", "Full Health = 2 coin", "Exit to shop", [=]() {}, player, hud);
	this->addChild(popup, 10000);
}

void GameScene::checkCollision() {
	if (player->state == State::isAttacking) {
		for (auto goblin : goblins) {
			if (goblin->minGroundY == player->minGroundY) {
				if (player->getScaleX() > 0) {
					if (goblin->getPositionX() > (player->getPositionX() - player->getDamageRange()) &&
						goblin->getPositionX() < player->getPositionX()) {
						attackGoblin(goblin, player->getAttackAnimationIndex());
					}

				}
				else if (player->getScaleX() < 0) {
					if (goblin->getPositionX() < (player->getPositionX() + player->getDamageRange()) &&
						goblin->getPositionX() > player->getPositionX()) {
						attackGoblin(goblin, player->getAttackAnimationIndex());
					}
				}
			}
		}
		for (auto skeleton : skeletons) {
			if (skeleton->minGroundY == player->minGroundY) {
				if (player->getScaleX() > 0) {
					if (skeleton->getPositionX() > (player->getPositionX() - player->getDamageRange()) &&
						skeleton->getPositionX() < player->getPositionX()) {
						attackSkeleton(skeleton, player->getAttackAnimationIndex());
					}

				}
				else if (player->getScaleX() < 0) {
					if (skeleton->getPositionX() < (player->getPositionX() + player->getDamageRange()) &&
						skeleton->getPositionX() > player->getPositionX()) {
						attackSkeleton(skeleton, player->getAttackAnimationIndex());
					}
				}
			}
		}
		if (boss->minGroundY == player->minGroundY) {
			if (player->getScaleX() > 0) {
				if (boss->getPositionX() > (player->getPositionX() - player->getDamageRange()) &&
					boss->getPositionX() < player->getPositionX()) {
					attackBoss(boss, player->getAttackAnimationIndex());
				}

			}
			else if (player->getScaleX() < 0) {
				if (boss->getPositionX() < (player->getPositionX() + player->getDamageRange()) &&
					boss->getPositionX() > player->getPositionX()) {
					attackBoss(boss, player->getAttackAnimationIndex());
				}
			}
		}
	}
}

void GameScene::attackGoblin(Goblin* goblin, int index) {
	CCLOG("%d", index);
	if (goblin->state != State::isTakingHit &&
		goblin->state != State::isDead &&
		index == 4 && goblin->getHealth() > 0) {
		CCLOG("Hit!");
		goblin->stopAllActions();
		goblin->velocityX = 0;
		goblin->state = State::isTakingHit;
		goblin->takeDamage(player->getDamage());
	}
}

void GameScene::attackSkeleton(Skeleton* skeleton, int index) {
	if (skeleton->state != State::isTakingHit &&
		skeleton->state != State::isDead &&
		index == 4 && skeleton->getHealth() > 0) {
		CCLOG("Hit!");
		skeleton->stopAllActions();
		skeleton->velocityX = 0;
		skeleton->state = State::isTakingHit;
		skeleton->takeDamage(player->getDamage());
	}
}

void GameScene::attackBoss(Boss* mush, int index) {
	if (mush->state != State::isTakingHit &&
		mush->state != State::isDead &&
		index == 4 && mush->getHealth() > 0) {
		CCLOG("Hit!");
		mush->stopAllActions();
		mush->velocityX = 0;
		mush->state = State::isTakingHit;
		mush->takeDamage(mush->getDamage());
	}
}

void GameScene::update(float dt) {
	whatKey(keyListener->keyState);

	if (player->getHealth() <= 0 && player->state != State::isDead) {
		player->stillState = State::isDying;
		player->state = player->stillState;
	}

	player->update();
	hud->update();
	boss->update();
	for (auto goblin : goblins) {
		goblin->update();
		if (goblin->getHealth() <= 0 && goblin->state != State::isDead) {
			goblin->stillState = State::isDying;
			goblin->state = goblin->stillState;
		}
	}
	for (auto skeleton : skeletons) {
		skeleton->update();
		if (skeleton->getHealth() <= 0 && skeleton->state != State::isDead) {
			skeleton->stillState = State::isDying;
			skeleton->state = skeleton->stillState;
		}
	}
	if (bossTrigger == false) {
		enemyLogic->chasePlayer(dt);
		skeletonLogic->chasePlayer(dt);
	}
	else {
		bossLogic->update(dt);

		for (auto goblin : goblins) {
			goblin->velocityX = 0;
		}
		for (auto skeleton : skeletons) {
			skeleton->velocityX = 0;
		}
	}

	checkCollision();

	checkActivePlatform();
	checkTakeCoin();

	shopButton();

	if (player->getPositionX() >= 6500) {
		bossTrigger = true;
		levelLeftEdge = 6500 - visibleSize.width / 2;
		levelRightEdge = 6500 + visibleSize.width / 2;
	}
	//playerNode->setPosition(Point(player->getPositionX() - origin.x - visibleSize.width / 2, player->getPositionY() - 130));
	//groundNode->setPositionX(playerNode->getPositionX() + player->velocityX);
	//bossNode->setPositionX(bossNode->getPositionX() + boss->velocityX);
}

void GameScene::pause(Ref* Sender) {

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume();
		this->removeChildByName("bg", true);
	}
	else {
		Director::getInstance()->pause();
		auto camera = Camera::getDefaultCamera();
		auto backgroundSprite = Sprite::create("main_menu_background.png");
		backgroundSprite->setName("bg");
		backgroundSprite->setGlobalZOrder(2);
		backgroundSprite->setContentSize(visibleSize);
		backgroundSprite->setPosition(Point(camera->getPositionX() + origin.x, visibleSize.height / 2 + origin.y));
		this->addChild(backgroundSprite, 1);

		auto resumeLabel = Label::createWithTTF("Resume", FONT_DEFINITION, 24);
		resumeLabel->setGlobalZOrder(3);
		auto resumeItem = MenuItemLabel::create(resumeLabel, CC_CALLBACK_1(GameScene::resumeScene, this));
		resumeItem->setPosition(Point(camera->getPositionX() + origin.x, visibleSize.height / 2 + origin.y + resumeItem->getContentSize().height * 2));

		auto menuLabel = Label::createWithTTF("Menu", FONT_DEFINITION, 24);
		menuLabel->setGlobalZOrder(3);
		auto menuItem = MenuItemLabel::create(menuLabel, CC_CALLBACK_1(GameScene::goToMenu, this));
		menuItem->setPosition(Point(camera->getPositionX() + origin.x, visibleSize.height / 2 + origin.y - resumeItem->getContentSize().height * 2));

		/*auto settingsLabel = Label::createWithTTF("Settings", FONT_DEFINITION, 24);
		settingsLabel->setGlobalZOrder(3);
		auto menuItem = MenuItemLabel::create(settingsLabel, CC_CALLBACK_1(GameScene::showSettings, this));*/

		auto menu = Menu::create(resumeItem, menuItem, NULL);
		menu->setPosition(Vec2::ZERO);
		menu->setName("menu1");
		this->addChild(menu, 10);
	}
}

void GameScene::listenKeyboard() {
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
		case EventKeyboard::KeyCode::KEY_D:
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyState[static_cast<int>(keyCode)] = true;
			keyPressed[static_cast<int>(keyCode)] = true;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			player->stopAllActions();
			// . . .
			player->update();
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			player->stopAllActions();
			// . . .
			player->update();
			break;
		}
	};
	eventListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_A:
		case EventKeyboard::KeyCode::KEY_D:
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			keyState[static_cast<int>(keyCode)] = false;
			keyReleased[static_cast<int>(keyCode)] = true;
			break;
		case EventKeyboard::KeyCode::KEY_SPACE:
			player->stopAllActions();
			// . . .
			player->update();
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			player->stopAllActions();
			// . . .
			player->update();
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}

void GameScene::resumeScene(Ref* Sender) {
	if (Director::getInstance()->isPaused()) {
		Director::getInstance()->resume();
		this->removeChildByName("bg", true);
		this->removeChildByName("menu1", true);
	}
}