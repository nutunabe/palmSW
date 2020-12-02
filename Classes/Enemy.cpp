#include "Enemy.h"
#include "Windows.h"

USING_NS_CC;

Enemy* Enemy::create(char* name, float health, float damage) {
	Enemy* enemy = new Enemy();
	if (enemy->init()) {
		enemy->setAnchorPoint(Point(0.5, 0.05));
		enemy->autorelease();
		enemy->initEnemy(name, health, damage);
		return enemy;
	}
	CC_SAFE_DELETE(enemy);
	return NULL;
}

void Enemy::initEnemy(char* name, float health, float damage) {
	char str[200] = { 0 };

	sprintf(str, "res/characters/%s.plist", name);

	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile(str);

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
	setScaleX(3.0);
}

Animate* Enemy::initAnimation(char* name, int initIndex, int finIndex, float dt) {
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int _i = initIndex; _i <= finIndex; _i++) {
		sprintf(str, "%s-%d.png", name, _i);
		frames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(frames, dt);
	return Animate::create(animation);
}

Animate* Enemy::initAnimation2(char* name, int initIndex, int finIndex, float dt) {
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

void Enemy::update()
{
	velocityY -= 9.81 * 0.1;
	setPositionY(getPositionY() + velocityY);
	if (getPositionY() < minGroundY) {
		setPositionY(minGroundY);
		velocityY = 0;
	}

	setPositionX(getPositionX() + velocityX);
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

void Enemy::idle() {
	runAction(RepeatForever::create(idleAnimate));
}

void Enemy::ready() {
	runAction(RepeatForever::create(readyAnimate));
}

void Enemy::run() {
	runAction(RepeatForever::create(runAnimate));
}

void Enemy::attack() {
	//char str[100];
	//sprintf(str, "%d", attackAnimate->getCurrentFrameIndex());
	//CCLOG(str);
	runAction(Repeat::create(attackAnimate, 1));
	if (attackAnimate->getCurrentFrameIndex() == 6) {
		state = stillState;
	}
}

void Enemy::jump() {
	runAction(RepeatForever::create(jumpAnimate));
	if (getPositionY() == minGroundY && velocityX != 0) {
		state = State::isRunning;
	}
	if (getPositionY() == minGroundY && velocityX == 0) {
		state = stillState;
	}
	// . . .
}

void Enemy::takeHit() {
	runAction(Repeat::create(takeHitAnimate, 1));
	if (takeHitAnimate->getCurrentFrameIndex() == 2) {
		state = stillState;
	}
}

void Enemy::die() {
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