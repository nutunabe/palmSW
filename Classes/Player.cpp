#include "Player.h"
#include "Windows.h"

USING_NS_CC;

Player* Player::create()
{
	Player* player = new Player();
	if (player->initWithFile("HelloSaddam.png"))
	{
		player->autorelease();
		player->initPlayer();
		player->listenKeyboard();
		player->scheduleUpdate();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{
	char str[200] = { 0 };
	direction = "right";
	is_moving = false;
	is_idle = false;
	is_attackPress = false;
	is_attacking = false;
	Vector<SpriteFrame*> idleFrames(4);
	Vector<SpriteFrame*> readyFrames(4);
	Vector<SpriteFrame*> runFrames(8);
	Vector<SpriteFrame*> attackFrames(8);

	auto spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("hero.plist");

	//Animation Ready
	for (int _i = 0; _i < 4; _i++) {
		sprintf(str, "ready%d.png", _i);
		readyFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}

	auto readyAnimation = Animation::createWithSpriteFrames(readyFrames, 0.15f);
	readyAnimate = Animate::create(readyAnimation);
	readyAnimate->retain();

	this->runAction(RepeatForever::create(readyAnimate));

	//Animation Run
	for (int _i = 0; _i < 8; _i++) {
		sprintf(str, "run%d.png", _i);
		runFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}

	auto runAnimation = Animation::createWithSpriteFrames(runFrames, 0.1f);
	runAnimate = Animate::create(runAnimation);
	runAnimate->retain();

	//Animation Attack
	for (int _i = 0; _i < 8; _i++) {
		sprintf(str, "attack%d.png", _i);
		attackFrames.pushBack(spritecache->getSpriteFrameByName(str));
	}

	auto attackAnimation = Animation::createWithSpriteFrames(attackFrames, 0.065f);
	attackAnimate = Animate::create(attackAnimation);
	attackAnimate->retain();

	this->setScale(3.0);
}

void Player::update(float dt)
{
	if (attackAnimate->getCurrentFrameIndex() == 7) {
		is_attacking = true;
	}
	if (this->getNumberOfRunningActions() == 0) {
		if (is_attackPress == true) {
			attack();
		}
		if (is_idle == false && is_attackPress == false) {
			idle();
			is_idle = true;
		}
	}
	if (direction == "right")
	{
		if (this->getScaleX() > 0)
			this->setScaleX(this->getScaleX() * -1);
		if (is_moving)
		{
			this->setPositionX(this->getPositionX() + 3);
		}
	}
	if (direction == "left")
	{
		if (this->getScaleX() < 0)
			this->setScaleX(this->getScaleX() * -1);
		if (is_moving)
		{
			this->setPositionX(this->getPositionX() - 3);
		}
	}
}

void Player::run(std::string directionParam)
{
	this->stopAllActions();

	if (direction == "left") {
		this->runAction(RepeatForever::create(runAnimate));
	}
	else {
		this->runAction(RepeatForever::create(runAnimate));
	}

	direction = directionParam;
	is_moving = true;
}

void Player::idle()
{
	is_moving = false;
	this->stopAllActions();

	if (direction == "left") {
		this->runAction(RepeatForever::create(readyAnimate));
	}
	else {
		this->runAction(RepeatForever::create(readyAnimate));
	}
}

void Player::attack()
{
	this->stopAllActions();
	this->runAction(Repeat::create(attackAnimate, 1));
	is_idle = false;
	is_moving = false;
	is_attacking = true;
}

void Player::listenKeyboard()
{
	auto eventListener = EventListenerKeyboard::create();
	eventListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_D:
			is_moving = true;
			direction = "right";
			run(direction);
			break;
		case EventKeyboard::KeyCode::KEY_A:
			is_moving = true;
			direction = "left";
			run(direction);
			break;
		case EventKeyboard::KeyCode::KEY_F:
			if (is_attacking == false) 
			{
				attack();
				is_attackPress = true;
			}
			break;
		}

	};
	eventListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
	{
		switch (keyCode) {
		case EventKeyboard::KeyCode::KEY_D:
			is_moving = false;
			direction = "right";
			idle();
			break;
		case EventKeyboard::KeyCode::KEY_A:
			is_moving = false;
			direction = "left";
			idle();
			break;
		case EventKeyboard::KeyCode::KEY_F:
			is_attackPress = false;
			break;
		}
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}