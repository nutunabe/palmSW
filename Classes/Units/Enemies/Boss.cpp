#include "Boss.h"
#include "Windows.h"

USING_NS_CC;

Boss* Boss::create()
{
	Boss* boss = new Boss();
	if (boss->init())
	{
		srand(time(nullptr));
		boss->setAnchorPoint(Point(0.5f, 0.5f));
		boss->autorelease();
		boss->initBoss();
		return boss;
	}
	CC_SAFE_DELETE(boss);
	return NULL;
}

void Boss::initBoss()
{
	scale = 6;
	width = 45 * scale;
	height = 45 * scale;
	paddingTop = -13 * scale;
	paddingBottom = -4 * scale;
	paddingLeft = 6 * scale;
	paddingRight = -6 * scale;

	stillState = State::isIdle;
	state = stillState;
	health = 100;
	stamina = 100;
	damage = 34;
	damageRange = width;
	velocityMax = 3;

	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/characters/mushroom.plist");

	// Animation Idle
	idleAnimate = initAnimation("Idle", 4, 0.15f);
	idleAnimate->retain();
	// Animation Run
	runAnimate = initAnimation("Run", 8, 0.1f);
	runAnimate->retain();
	// Animation Attack
	attackAnimate = initAnimation("Attack", 8, 0.075f, "");
	attackAnimate->retain();
	// Animation Attack2
	attack2Animate = initAnimation("Attack2", 8, 0.075f, "");
	attack2Animate->retain();
	// Animation Attack3
	attack3Animate = initAnimation("Attack3", 11, 0.075f, "");
	attack3Animate->retain();
	// Animation Take Hit
	takeHitAnimate = initAnimation("Take Hit", 4, 0.05f, "");
	takeHitAnimate->retain();
	// Animation Death
	deathAnimate = initAnimation("Death", 4, 0.2f, "");
	deathAnimate->retain();

	// Dead
	Vector<SpriteFrame*> deadFrame;
	deadFrame.pushBack(spritecache->getSpriteFrameByName("Death-3.png"));
	auto deadAnimation = Animation::createWithSpriteFrames(deadFrame, 1.f);
	deadAnimate = Animate::create(deadAnimation);
	deadAnimate->retain();

	setScaleY(scale);
	setScaleX(-1 * scale);
	spritecache->destroyInstance();

	auto hBBackground = Sprite::create("block2.png");
	hBBackground->setAnchorPoint(Point(0.5, 1));
	hBBackground->setPosition(Point(this->getPositionX() + 75, this->getPositionY() + 100));
	hBBackground->setScale(0.1);
	hBBackground->setName("hb");
	this->addChild(hBBackground);

	hpboss = ui::LoadingBar::create("block.png");
	hpboss->setAnchorPoint(Point(0.5, 1));
	hpboss->setPosition(Point(this->getPositionX() + 75, this->getPositionY() + 100));
	hpboss->setDirection(ui::LoadingBar::Direction::RIGHT);
	hpboss->setPercent(health);
	hpboss->setScale(0.1);
	this->addChild(hpboss);
}

void Boss::update()
{
	if (state != State::isDead && state != State::isDying) {
		if (getScaleX() > 0) {
			hpboss->setDirection(ui::LoadingBar::Direction::LEFT);
		}
		else {
			hpboss->setDirection(ui::LoadingBar::Direction::RIGHT);
		}
		hpboss->setPercent(health);
	}

	setPositionX(getPositionX() + velocityX);

	getTexture()->setAliasTexParameters();
	switch (state) {
	case State::isIdle:
		idle();
		// . . .
		break;
	case State::isRunning:
		run();
		// . . .
		break;
	case State::isAttacking:
		switch (mode) {
		case FightMode::punch:
			attack1();
			break;
		case FightMode::bite:
			attack2();
			break;
		case FightMode::sturmtiger:
			attack3();
			break;
		}
		// . . .
		break;
	case State::isTakingHit:
		takeHit();
		// . . .
		break;
	case State::isDying:
		die();
		this->removeChild(hpboss, true);
		this->removeChildByName("hb", true);
		// . . .
		break;
	case State::isDead:
		runAction(RepeatForever::create(deadAnimate));
		// . . .
		break;
	default: break;
	}
}

int Boss::getAttackAnimationIndex() {
	switch (mode) {
	case FightMode::punch:
		return attackAnimate->getCurrentFrameIndex();
		break;
	case FightMode::bite:
		return attack2Animate->getCurrentFrameIndex();
		break;
	case FightMode::sturmtiger:
		return attack3Animate->getCurrentFrameIndex();
		break;
	}
}

void Boss::idle() {
	runAction(RepeatForever::create(idleAnimate));
}

void Boss::run() {
	runAction(RepeatForever::create(runAnimate));
}

void Boss::attack1() {
	runAction(Repeat::create(attackAnimate, 1));
	if (attackAnimate->getCurrentFrameIndex() == 8) {
		stopAllActions();
		attackAnimate->update(0);
		state = stillState;
	}
}

void Boss::attack2() {
	runAction(Repeat::create(attack2Animate, 1));
	if (attack2Animate->getCurrentFrameIndex() == 8) {
		stopAllActions();
		attack2Animate->update(0);
		state = stillState;
	}
}

void Boss::attack3() {
	runAction(Repeat::create(attack3Animate, 1));
	if (attack3Animate->getCurrentFrameIndex() == 11) {
		stopAllActions();
		attack3Animate->update(0);
		state = stillState;
	}
}

void Boss::takeHit() {
	runAction(Repeat::create(takeHitAnimate, 1));
	if (takeHitAnimate->getCurrentFrameIndex() == 2) {
		stopAllActions();
		takeHitAnimate->update(0);
		state = stillState;
	}
}

void Boss::die() {
	runAction(Repeat::create(deathAnimate, 1));
	if (deathAnimate->getCurrentFrameIndex() == 3) {
		stopAllActions();
		stillState = State::isDead;
		state = stillState;
	}
}