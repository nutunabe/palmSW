#include "Player.h"
#include "Windows.h"
#include "DeathScreen.h"

USING_NS_CC;

Player* Player::create()
{
	Player* player = new Player();
	if (player->init())
	{
		player->setAnchorPoint(Point(0.5f, 0.5f));
		player->autorelease();
		player->initPlayer();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{
	scale = 3.0;
	width = 48 * scale;
	height = 48 * scale;
	paddingTop = -11 * scale;
	paddingBottom = 2 * scale;
	paddingLeft = 8 * scale;
	paddingRight = -8 * scale;

	stillState = State::isReady;
	state = stillState;
	health = 100;
	stamina = 100;
	damage = 20;
	damageRange = width;
	velocityMax = 5;

	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/characters/hero.plist");

	// Animation Idle
	idleAnimate = initAnimation("Idle", 4, 0.15f);
	idleAnimate->retain();
	// Animation Ready
	readyAnimate = initAnimation("Ready", 4, 0.15f);
	readyAnimate->retain();
	// Animation Run
	runAnimate = initAnimation("Run", 8, 0.1f);
	runAnimate->retain();
	// Animation Attack
	attackAnimate = initAnimation("Attack", 8, 0.075f, "");
	attackAnimate->retain();
	// Animation Take Hit
	takeHitAnimate = initAnimation("Take Hit", 2, 0.05f, "");
	takeHitAnimate->retain();
	// Animation Death
	deathAnimate = initAnimation("Death", 3, 0.2f, "");
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

	setScaleY(scale);
	setScaleX(-1 * scale);
	spritecache->destroyInstance();

	std::ifstream ifs("../Resources/Data.json");
	rapidjson::IStreamWrapper isw(ifs);

	doc.ParseStream(isw);
	assert(doc.IsObject());
	assert(doc.HasMember("soundfxVolume"));
	assert(doc["soundfxVolume"].IsFloat());
	swordswingVolume = doc["soundfxVolume"].GetFloat();
}

void Player::update()
{
	//CCLOG("%f", health);

	velocityY -= 9.81 * 0.1;
	setPositionY(getPositionY() + velocityY);

	if (getBottom() < minGroundY) {
		setPositionY(minGroundY + height / 2 - paddingBottom);
		velocityY = 0;
	}

	if (stamina < 100) {
		stamina += 0.1;
	}

	setPositionX(getPositionX() + velocityX);

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
		run();
		// . . .
		break;
	case State::isAttacking: {
		attack();
		// . . .
		break; }
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

int Player::getAttackAnimationIndex() {
	return attackAnimate->getCurrentFrameIndex();
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
	runAction(Repeat::create(attackAnimate, 1));
	if (attackAnimate->getCurrentFrameIndex() == 1 
		&& AudioEngine::getState(swordswing) != AudioEngine::AudioState::PLAYING) {
			swordswing = AudioEngine::play2d("res/sounds/swordswing.mp3", false, swordswingVolume);
	}
	if (attackAnimate->getCurrentFrameIndex() == 6) {
		state = stillState;
	}
}

void Player::jump() {
	runAction(RepeatForever::create(jumpAnimate));
	if (getBottom() == minGroundY && velocityX != 0) {
		state = State::isRunning;
	}
	if (getBottom() == minGroundY && velocityX == 0) {
		state = stillState;
	}
	// . . .
}

void Player::takeHit() {
	runAction(Repeat::create(takeHitAnimate, 1));
	if (takeHitAnimate->getCurrentFrameIndex() == 2) {
		stopAllActions();
		takeHitAnimate->update(0);
		state = stillState;
	}
}

void Player::die() {
	runAction(Repeat::create(deathAnimate, 1));
	if (deathAnimate->getCurrentFrameIndex() == 3) {
		stopAllActions();
		stillState = State::isDead;
		state = stillState;
		auto scene = DeathScreen::createScene();
		Director::getInstance()->replaceScene(TransitionFade::create(0.5, scene));
	}
}