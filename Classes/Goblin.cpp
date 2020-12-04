#include "Goblin.h"
#include "Windows.h"

USING_NS_CC;

Goblin* Goblin::create()
{
	Goblin* goblin = new Goblin();
	if (goblin->init())
	{
		goblin->setAnchorPoint(Point(0.5, 0.05));
		goblin->autorelease();
		goblin->initGoblin();
		return goblin;
	}
	CC_SAFE_DELETE(goblin);
	return NULL;
}

void Goblin::initGoblin()
{
	char str[200] = { 0 };

	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/characters/goblin.plist");

	// Animation Idle
	idleAnimate = initAnimation("Idle", 0, 3, 0.15f);
	idleAnimate->retain();
	// Animation Run
	runAnimate = initAnimation("Run", 0, 7, 0.1f);
	runAnimate->retain();
	// Animation Attack
	attackAnimate = initAnimation2("Attack", 0, 7, 0.075f);
	attackAnimate->retain();
	// Animation Take Hit
	takeHitAnimate = initAnimation2("Take Hit", 0, 3, 0.05f);
	takeHitAnimate->retain();
	// Animation Death
	deathAnimate = initAnimation2("Death", 0, 3, 0.2f);
	deathAnimate->retain();

	// Dead
	Vector<SpriteFrame*> deadFrame;
	deadFrame.pushBack(spritecache->getSpriteFrameByName("Death-3.png"));
	auto deadAnimation = Animation::createWithSpriteFrames(deadFrame, 1.f);
	deadAnimate = Animate::create(deadAnimation);
	deadAnimate->retain();

	setScaleY(3.0);
	setScaleX(3.0);
}

Animate* Goblin::initAnimation(char* name, int initIndex, int finIndex, float dt) {
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int _i = initIndex; _i <= finIndex; _i++) {
		sprintf(str, "%s-%d.png", name, _i);
		frames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(frames, dt);
	return Animate::create(animation);
}

Animate* Goblin::initAnimation2(char* name, int initIndex, int finIndex, float dt) {
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

void Goblin::update()
{
	setPositionX(getPositionX() + velocityX);
	//if (velocity == 0 && getPositionY() == 120) {
	//	state = stillState;
	//}

	getTexture()->setAliasTexParameters();
	switch (state) {
	case gState::isIdle:
		idle();
		// . . .
		break;
	case gState::isRunning:
		//borderStuck();
		run();
		// . . .
		break;
	case gState::isAttacking:
		attack();
		// . . .
		break;
	case gState::isTakingHit:
		takeHit();
		// . . .
		break;
	case gState::isDying:
		die();
		// . . .
		break;
	case gState::isDead:
		runAction(RepeatForever::create(deadAnimate));
		// . . .
		break;
	default: break;
	}
}

void Goblin::idle() {
	runAction(RepeatForever::create(idleAnimate));
}

void Goblin::run() {
	runAction(RepeatForever::create(runAnimate));
}

void Goblin::attack() {
	//char str[100];
	//sprintf(str, "%d", attackAnimate->getCurrentFrameIndex());
	//CCLOG(str);
	runAction(Repeat::create(attackAnimate, 1));
	if (attackAnimate->getCurrentFrameIndex() == 6) {
		stopAllActions();
	}
}

void Goblin::takeHit() {
	runAction(Repeat::create(takeHitAnimate, 1));
	if (takeHitAnimate->getCurrentFrameIndex() == 2) {
		state = stillState;
	}
}

void Goblin::die() {
	runAction(Repeat::create(deathAnimate, 1));
	if (deathAnimate->getCurrentFrameIndex() == 3) {
		stopAllActions();
		stillState = gState::isDead;
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