#include "Skeleton.h"
#include "Windows.h"

USING_NS_CC;

Skeleton* Skeleton::create()
{
	Skeleton* skeleton = new Skeleton();
	if (skeleton->init())
	{
		srand(time(nullptr));
		skeleton->setAnchorPoint(Point(0.5f, 0.5f));
		skeleton->autorelease();
		skeleton->initSkeleton();
		return skeleton;
	}
	CC_SAFE_DELETE(skeleton);
	return NULL;
}

void Skeleton::initSkeleton()
{
	scale = 2.5;
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
	damage = 20;
	damageRange = width;
	velocityMax = 2;

	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/characters/skeleton1.plist");

	// Animation Idle
	idleAnimate = initAnimation("Idle", 4, 0.15f);
	idleAnimate->retain();
	// Animation Run
	runAnimate = initAnimation("Walk", 4, 0.1f);
	runAnimate->retain();
	// Animation Attack
	attackAnimate = initAnimation("Attack", 8, 0.075f, "");
	attackAnimate->retain();
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
	hBBackground->setPosition(Point(this->getPositionX() + 80, this->getPositionY() + 105));
	hBBackground->setScale(0.1);
	hBBackground->setName("hb");
	this->addChild(hBBackground);

	hpskeleton = ui::LoadingBar::create("block.png");
	hpskeleton->setAnchorPoint(Point(0.5, 1));
	hpskeleton->setPosition(Point(this->getPositionX() + 80, this->getPositionY() + 105));
	hpskeleton->setDirection(ui::LoadingBar::Direction::RIGHT);
	hpskeleton->setPercent(health);
	hpskeleton->setScale(0.1);
	this->addChild(hpskeleton);
}

void Skeleton::update()
{
	if (state != State::isDead && state != State::isDying) {
		if (getScaleX() > 0) {
			hpskeleton->setDirection(ui::LoadingBar::Direction::LEFT);
		}
		else {
			hpskeleton->setDirection(ui::LoadingBar::Direction::RIGHT);
		}
		hpskeleton->setPercent(health);
	}

	setPositionX(getPositionX() + velocityX);

	getTexture()->setAliasTexParameters();
	switch (state) {
	case State::isIdle:
		idle();
		break;
	case State::isRunning:
		run();
		break;
	case State::isAttacking:
		attack();
		break;
	case State::isTakingHit:
		takeHit();
		break;
	case State::isDying:
		die();
		this->removeChild(hpskeleton, true);
		this->removeChildByName("hb", true);
		break;
	case State::isDead:
		runAction(RepeatForever::create(deadAnimate));
		break;
	default: break;
	}
}

int Skeleton::getAttackAnimationIndex() {
	return attackAnimate->getCurrentFrameIndex();
}

void Skeleton::idle() {
	runAction(RepeatForever::create(idleAnimate));
}

void Skeleton::run() {
	runAction(RepeatForever::create(runAnimate));
}

void Skeleton::attack() {
	runAction(Repeat::create(attackAnimate, 1));
	if (attackAnimate->getCurrentFrameIndex() == 8) {
		stopAllActions();
		attackAnimate->update(0);
		state = stillState;
	}
}

void Skeleton::takeHit() {
	runAction(Repeat::create(takeHitAnimate, 1));
	if (takeHitAnimate->getCurrentFrameIndex() == 2) {
		stopAllActions();
		takeHitAnimate->update(0);
		state = stillState;
	}
}

void Skeleton::die() {
	runAction(Repeat::create(deathAnimate, 1));
	if (deathAnimate->getCurrentFrameIndex() == 3) {
		stopAllActions();
		stillState = State::isDead;
		state = stillState;
	}
}