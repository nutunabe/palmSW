#ifndef __GOBLIN__
#define __GOBLIN__

#include "cocos2d.h"

USING_NS_CC;

enum class gState {
	isIdle,
	isRunning,
	isAttacking,
	isTakingHit,
	isDying,
	isDead
};

class Goblin : public cocos2d::Sprite {
public:
	gState stillState = gState::isIdle;
	gState state = stillState;
	float velocityMax = 1;
	float velocityX;
	float velocityY = 0;
	int minGroundY;

	void update();
	static Goblin* create(void);

private:
	Animate* idleAnimate;
	Animate* runAnimate;
	Animate* attackAnimate;
	Animate* takeHitAnimate;
	Animate* deathAnimate;
	Animate* deadAnimate;
	//Animate* flyingAnimate;
	//Animate* fallingAnimate;
	SpriteFrameCache* spritecache;

	bool keyState[256];
	bool stateSwitched = false;

	Animate* initAnimation(char* name, int initIndex, int finIndex, float dt);
	Animate* initAnimation2(char* name, int initIndex, int finIndex, float dt);
	void initGoblin();
	void idle();
	void run();
	void attack();
	void takeHit();
	void die();
	//void borderStuck();
};

#endif