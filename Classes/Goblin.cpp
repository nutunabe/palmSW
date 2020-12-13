#include "Goblin.h"
#include "Windows.h"

USING_NS_CC;

Goblin* Goblin::create()
{
	Goblin* goblin = new Goblin();
	if (goblin->init())
	{
		goblin->setAnchorPoint(Point(0.5, 0));
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

	gspritecache = SpriteFrameCache::getInstance();
	gspritecache->addSpriteFramesWithFile("res/characters/goblin.plist");

	// Animation Idle
	gidleAnimate = initAnimation("Idle", 0, 3, 0.15f);
	gidleAnimate->retain();
	// Animation Run
	grunAnimate = initAnimation("Run", 0, 7, 0.1f);
	grunAnimate->retain();
	// Animation Attack
	gattackAnimate = initAnimation2("Attack", 0, 7, 0.075f);
	gattackAnimate->retain();
	// Animation Take Hit
	gtakeHitAnimate = initAnimation2("Take Hit", 0, 3, 0.05f);
	gtakeHitAnimate->retain();
	// Animation Death
	gdeathAnimate = initAnimation2("Death", 0, 3, 0.2f);
	gdeathAnimate->retain();

	// Dead
	Vector<SpriteFrame*> deadFrame;
	deadFrame.pushBack(gspritecache->getSpriteFrameByName("Death-3.png"));
	auto deadAnimation = Animation::createWithSpriteFrames(deadFrame, 1.f);
	gdeadAnimate = Animate::create(deadAnimation);
	gdeadAnimate->retain();

	setScaleY(3.0);
	setScaleX(3.0);

	gspritecache->destroyInstance();

	auto hBBackground = Sprite::create("block2.png");
	hBBackground->setAnchorPoint(Point(0.5, 1));
	hBBackground->setPosition(Point(this->getPositionX() + 75, this->getPositionY() + 100));
	hBBackground->setScale(0.1);
	this->addChild(hBBackground);

	hpgoblin = ui::LoadingBar::create("block.png");
	hpgoblin->setAnchorPoint(Point(0.5, 1));
	hpgoblin->setPosition(Point(this->getPositionX() + 75, this->getPositionY() + 100));
	hpgoblin->setDirection(ui::LoadingBar::Direction::LEFT);
	hpgoblin->setPercent(health);
	hpgoblin->setScale(0.1);
	this->addChild(hpgoblin);
}

Animate* Goblin::initAnimation(char* name, int initIndex, int finIndex, float dt) {
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int _i = initIndex; _i <= finIndex; _i++) {
		sprintf(str, "%s-%d.png", name, _i);
		frames.pushBack(gspritecache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(frames, dt);
	return Animate::create(animation);
}

Animate* Goblin::initAnimation2(char* name, int initIndex, int finIndex, float dt) {
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int _i = initIndex; _i <= finIndex; _i++) {
		sprintf(str, "%s-%d.png", name, _i);
		frames.pushBack(gspritecache->getSpriteFrameByName(str));
	}
	frames.pushBack(gspritecache->getSpriteFrameByName(str));
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
		runAction(RepeatForever::create(gdeadAnimate));
		// . . .
		break;
	default: break;
	}
}

void Goblin::idle() {
	runAction(RepeatForever::create(gidleAnimate));
}

void Goblin::run() {
	runAction(RepeatForever::create(grunAnimate));
}

void Goblin::attack() {
	//char str[100];
	//sprintf(str, "%d", attackAnimate->getCurrentFrameIndex());
	//CCLOG(str);
	runAction(Repeat::create(gattackAnimate, 1));
	if (gattackAnimate->getCurrentFrameIndex() == 8) {
		stopAllActions(); 
		gattackAnimate->update(0);
	}
}

void Goblin::takeHit() {
	runAction(Repeat::create(gtakeHitAnimate, 1));
	if (gtakeHitAnimate->getCurrentFrameIndex() == 2) {
		state = stillState;
	}
}

void Goblin::die() {
	runAction(Repeat::create(gdeathAnimate, 1));
	if (gdeathAnimate->getCurrentFrameIndex() == 3) {
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