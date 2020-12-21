#include "Goblin.h"
#include "Windows.h"

USING_NS_CC;

Goblin* Goblin::create()
{
	Goblin* goblin = new Goblin();
	if (goblin->init())
	{
		srand(time(nullptr));
		goblin->setAnchorPoint(Point(0.5f, 0.5f));
		goblin->autorelease();
		goblin->initGoblin();
		return goblin;
	}
	CC_SAFE_DELETE(goblin);
	return NULL;
}

void Goblin::initGoblin()
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
	spritecache->addSpriteFramesWithFile("res/characters/goblin.plist");

	// Animation Idle
	idleAnimate = initAnimation("Idle", 4, 0.15f);
	idleAnimate->retain();
	// Animation Run
	runAnimate = initAnimation("Run", 8, 0.1f);
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
	hBBackground->setPosition(Point(this->getPositionX() + 75, this->getPositionY() + 100));
	hBBackground->setScale(0.1);
	hBBackground->setName("hb");
	this->addChild(hBBackground);

	hpgoblin = ui::LoadingBar::create("block.png");
	hpgoblin->setAnchorPoint(Point(0.5, 1));
	hpgoblin->setPosition(Point(this->getPositionX() + 75, this->getPositionY() + 100));
	hpgoblin->setDirection(ui::LoadingBar::Direction::RIGHT);
	hpgoblin->setPercent(health);
	hpgoblin->setScale(0.1);
	this->addChild(hpgoblin);
}

void Goblin::update()
{
	if (state != State::isDead && state != State::isDying) {
		if (getScaleX() > 0) {
			hpgoblin->setDirection(ui::LoadingBar::Direction::LEFT);
		}
		else {
			hpgoblin->setDirection(ui::LoadingBar::Direction::RIGHT);
		}
		hpgoblin->setPercent(health);
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
		attack();
		// . . .
		break;
	case State::isTakingHit:
		takeHit();
		// . . .
		break;
	case State::isDying:
		die();
		this->removeChild(hpgoblin, true);
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

int Goblin::getAttackAnimationIndex() {
	return attackAnimate->getCurrentFrameIndex();
}

void Goblin::idle() {
	runAction(RepeatForever::create(idleAnimate));
}

void Goblin::run() {
	runAction(RepeatForever::create(runAnimate));
}

void Goblin::attack() {
	runAction(Repeat::create(attackAnimate, 1));
	if (attackAnimate->getCurrentFrameIndex() == 8) {
		stopAllActions();
		attackAnimate->update(0);
		state = stillState;
	}
}

void Goblin::takeHit() {
	runAction(Repeat::create(takeHitAnimate, 1));
	if (takeHitAnimate->getCurrentFrameIndex() == 2) {
		stopAllActions();
		takeHitAnimate->update(0);
		state = stillState;
	}
}

void Goblin::die() {
	runAction(Repeat::create(deathAnimate, 1));
	if (deathAnimate->getCurrentFrameIndex() == 3) {
		stopAllActions();
		stillState = State::isDead;
		state = stillState;
	}
}