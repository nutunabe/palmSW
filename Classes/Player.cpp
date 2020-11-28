//#include "Player.h"
//#include "Windows.h"
//
//USING_NS_CC;
//
//Player* Player::create()
//{
//	Player* player = new Player();
//	if (player->initWithFile("HelloSaddam.png"))
//	{
//		player->autorelease();
//		player->initPlayer();
//		player->listenKeyboard();
//		player->scheduleUpdate();
//		return player;
//	}
//	CC_SAFE_DELETE(player);
//	return NULL;
//}
//
//void Player::initPlayer()
//{
//	char str[200] = { 0 };
//	direction = "right";
//	is_moving = false;
//	is_idle = false;
//	is_attackPress = false;
//	is_attacking = false;
//	visibleSize = Director::getInstance()->getVisibleSize();
//	Vector<SpriteFrame*> idleFrames(4);
//	Vector<SpriteFrame*> readyFrames(4);
//	Vector<SpriteFrame*> runFrames(8);
//	Vector<SpriteFrame*> attackFrames(8);
//
//	auto spritecache = SpriteFrameCache::getInstance();
//	spritecache->addSpriteFramesWithFile("hero.plist");
//
//	//Animation Ready
//	for (int _i = 0; _i < 4; _i++) {
//		sprintf(str, "ready%d.png", _i);
//		readyFrames.pushBack(spritecache->getSpriteFrameByName(str));
//	}
//
//	auto readyAnimation = Animation::createWithSpriteFrames(readyFrames, 0.15f);
//	readyAnimate = Animate::create(readyAnimation);
//	readyAnimate->retain();
//
//	this->runAction(RepeatForever::create(readyAnimate));
//
//	//Animation Run
//	for (int _i = 0; _i < 8; _i++) {
//		sprintf(str, "run%d.png", _i);
//		runFrames.pushBack(spritecache->getSpriteFrameByName(str));
//	}
//
//	auto runAnimation = Animation::createWithSpriteFrames(runFrames, 0.1f);
//	runAnimate = Animate::create(runAnimation);
//	runAnimate->retain();
//
//	//Animation Attack
//	for (int _i = 0; _i < 8; _i++) {
//		sprintf(str, "attack%d.png", _i);
//		attackFrames.pushBack(spritecache->getSpriteFrameByName(str));
//	}
//
//	auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.065f);
//	attackAnimate = Animate::create(attackAnimation);
//	attackAnimate->retain();
//
//	this->setScale(3.0);
//}
//
//void Player::update(float dt)
//{
//	if (attackAnimate->getCurrentFrameIndex() == 7) {
//		is_attacking = true;
//	}
//	if (this->getNumberOfRunningActions() == 0) {
//		if (is_attackPress == true) {
//			attack();
//		}
//		if (is_idle == false && is_attackPress == false) {
//			idle();
//			is_idle = true;
//		}
//	}
//	if (direction == "right")
//	{
//		if (this->getScaleX() > 0)
//			this->setScaleX(this->getScaleX() * -1);
//		if (is_moving && this->getPositionX() < visibleSize.width - visibleSize.width / 6)
//		{
//			this->setPositionX(this->getPositionX() + 3);
//		}
//	}
//	if (direction == "left")
//	{
//		if (this->getScaleX() < 0)
//			this->setScaleX(this->getScaleX() * -1);
//		if (is_moving && this->getPositionX() > visibleSize.width / 6)
//		{
//			this->setPositionX(this->getPositionX() - 3);
//		}
//	}
//}
//
//void Player::run(std::string directionParam)
//{
//	this->stopAllActions();
//
//	if (direction == "left") {
//		this->runAction(RepeatForever::create(runAnimate));
//	}
//	else {
//		this->runAction(RepeatForever::create(runAnimate));
//	}
//
//	direction = directionParam;
//	is_moving = true;
//}
//
//void Player::idle()
//{
//	is_moving = false;
//	this->stopAllActions();
//
//	if (direction == "left") {
//		this->runAction(RepeatForever::create(readyAnimate));
//	}
//	else {
//		this->runAction(RepeatForever::create(readyAnimate));
//	}
//}
//
//void Player::attack()
//{
//	this->stopAllActions();
//	this->runAction(Repeat::create(attackAnimate, 1));
//	is_idle = false;
//	is_moving = false;
//	is_attacking = true;
//}
//
//void Player::listenKeyboard()
//{
//	auto eventListener = EventListenerKeyboard::create();
//	eventListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
//	{
//		switch (keyCode) {
//		case EventKeyboard::KeyCode::KEY_D:
//			is_moving = true;
//			direction = "right";
//			run(direction);
//			break;
//		case EventKeyboard::KeyCode::KEY_A:
//			is_moving = true;
//			direction = "left";
//			run(direction);
//			break;
//		case EventKeyboard::KeyCode::KEY_F:
//			if (is_attacking == false) 
//			{
//				attack();
//				is_attackPress = true;
//			}
//			break;
//		}
//
//	};
//	eventListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
//	{
//		switch (keyCode) {
//		case EventKeyboard::KeyCode::KEY_D:
//			is_moving = false;
//			direction = "right";
//			idle();
//			break;
//		case EventKeyboard::KeyCode::KEY_A:
//			is_moving = false;
//			direction = "left";
//			idle();
//			break;
//		case EventKeyboard::KeyCode::KEY_F:
//			is_attackPress = false;
//			break;
//		}
//	};
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
//}

#include "Player.h"
#include "Windows.h"

USING_NS_CC;

Player* Player::create()
{
	Player* player = new Player();
	if (player->init())
	{
		player->autorelease();
		player->initPlayer();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{
	char str[200] = { 0 };

	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/characters/hero.plist");

	// Animation Idle
	idleAnimate = initAnimation("Idle", 0, 3, 0.15f);
	idleAnimate->retain();
	// Animation Ready
	readyAnimate = initAnimation("Ready", 0, 3, 0.15f);
	readyAnimate->retain();
	// Animation Run
	runAnimate = initAnimation("Run", 0, 7, 0.1f);
	runAnimate->retain();
	// Animation Attack
	attackAnimate = initAnimation2("Attack", 2, 7, 0.075f);
	attackAnimate->retain();
	// Animation Take Hit
	takeHitAnimate = initAnimation2("Take Hit", 0, 1, 0.05f);
	takeHitAnimate->retain();
	// Animation Jump
	//jumpAnimate = initAnimation2("Jump", 0, 1, 0.1f);
	//jumpAnimate->retain();
	// Animation Death
	deathAnimate = initAnimation2("Death", 0, 2, 0.2f);
	deathAnimate->retain();

	// Animation Jump
	Vector<SpriteFrame*> jumpFrame;
	jumpFrame.pushBack(spritecache->getSpriteFrameByName("fly.png"));
	auto jumpAnimation = Animation::createWithSpriteFrames(jumpFrame, 1.f);
	jumpAnimate = Animate::create(jumpAnimation);
	jumpAnimate->retain();

	// Dead
	Vector<SpriteFrame*> deadFrame;
	deadFrame.pushBack(spritecache->getSpriteFrameByName("dead.png"));
	auto deadAnimation = Animation::createWithSpriteFrames(deadFrame, 1.f);
	deadAnimate = Animate::create(deadAnimation);
	deadAnimate->retain();

	setScaleY(3.0);
	setScaleX(-3.0);
}

Animate* Player::initAnimation(char* name, int initIndex, int finIndex, float dt) {
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int _i = initIndex; _i <= finIndex; _i++) {
		sprintf(str, "%s-%d.png", name, _i);
		frames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(frames, dt);
	return Animate::create(animation);
}

Animate* Player::initAnimation2(char* name, int initIndex, int finIndex, float dt) {
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int _i = initIndex; _i <= finIndex; _i++) {
		sprintf(str, "%s-%d.png", name, _i);
		frames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	frames.pushBack(spritecache->getSpriteFrameByName(str));
	auto animation = Animation::createWithSpriteFrames(frames, dt);
	return Animate::create(animation);
}

void Player::update()
{
	YV -= 9.81 * 0.1;
	setPositionY(getPositionY() + YV);
	if (getPositionY() < 120) {
		setPositionY(120);
	}

	setPositionX(getPositionX() + velocity);
	//if (velocity == 0 && getPositionY() == 120) {
	//	state = stillState;
	//}

	getTexture()->setAliasTexParameters();
	switch (state) {
	case State::isIdle:
		idle();
		// . . .
		break;
	case State::isReady:
		ready();
		// . . .
		break;
	case State::isRunning:
		//borderStuck();
		run();
		// . . .
		break;
	case State::isAttacking:
		attack();
		// . . .
		break;
	case State::isJumping:
		jump();
		// . . .
		break;
	case State::isTakingHit:
		takeHit();
		// . . .
		break;
	case State::isDying:
		die();
		// . . .
		break;
	case State::isDead:
		runAction(RepeatForever::create(deadAnimate));
		// . . .
		break;
	default: break;
	}
}

void Player::idle() {
	runAction(RepeatForever::create(idleAnimate));
}

void Player::ready() {
	runAction(RepeatForever::create(readyAnimate));
}

void Player::run() {
	runAction(RepeatForever::create(runAnimate));
}

void Player::attack() {
	//char str[100];
	//sprintf(str, "%d", attackAnimate->getCurrentFrameIndex());
	//CCLOG(str);
	runAction(Repeat::create(attackAnimate, 1));
	if (attackAnimate->getCurrentFrameIndex() == 6) {
		state = stillState;
	}
}

void Player::jump() {
	runAction(RepeatForever::create(jumpAnimate));
	if (getPositionY() == 120 && velocity != 0) {
		state = State::isRunning;
	}
	if (getPositionY() == 120 && velocity == 0) {
		state = stillState;
	}
	// . . .
}

void Player::takeHit() {
	runAction(Repeat::create(takeHitAnimate, 1));
	if (takeHitAnimate->getCurrentFrameIndex() == 2) {
		state = stillState;
	}
}

void Player::die() {
	runAction(Repeat::create(deathAnimate, 1));
	if (deathAnimate->getCurrentFrameIndex() == 3) {
		stopAllActions();
		stillState = State::isDead;
		state = stillState;
	}
}

/*void Player::borderStuck() {
	Size visibleSize = Director::getInstance()->getVisibleSize();
	if (getPositionX() < visibleSize.width - visibleSize.width / 6) {
		setPositionX(getPositionX() + velocity);
	}
	if ()
}*/