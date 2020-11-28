//#ifndef _PLAYER_
//#define _PLAYER_
//
//#include "cocos2d.h"
//#include "Leveling.h"
//
//USING_NS_CC;
//
//class Player : public cocos2d::Sprite {
//public:
//	Animate* idleAnimate;
//	Animate* readyAnimate;
//	Animate* runAnimate;
//	Animate* attackAnimate;
//
//	static Player* create(void);
//	void run(std::string direction);
//	void idle();
//	void attack();
//
//private:
//	bool is_moving;
//	bool is_idle;
//	bool is_attackPress;
//	bool is_attacking;
//	std::string direction;
//	Size visibleSize;
//
//	void initPlayer();
//	void listenKeyboard();
//	void update(float dt);
//};
//
//#endif

#ifndef __PLAYER__
#define __PLAYER__

#include "cocos2d.h"

USING_NS_CC;

enum class State {
	isIdle,
	isReady,
	isRunning,
	isAttacking,
	isJumping,
	isTakingHit,
	isDying,
	isDead
};

class Player : public cocos2d::Sprite {
public:
	State stillState = State::isReady;
	State state = stillState;
	int maxVelocity = 5;
	int velocity;
	int minGroundY;

	float YV = 0;

	void update();
	static Player* create(void);

private:
	Animate* idleAnimate;
	Animate* readyAnimate;
	Animate* runAnimate;
	Animate* attackAnimate;
	Animate* takeHitAnimate;
	Animate* jumpAnimate;
	Animate* deathAnimate;
	Animate* deadAnimate;
	//Animate* flyingAnimate;
	//Animate* fallingAnimate;
	SpriteFrameCache* spritecache;

	bool keyState[256];
	bool stateSwitched = false;

	Animate* initAnimation(char* name, int initIndex, int finIndex, float dt);
	Animate* initAnimation2(char* name, int initIndex, int finIndex, float dt);
	void initPlayer();
	void idle();
	void ready();
	void run();
	void attack();
	void jump();
	void takeHit();
	void die();
	//void borderStuck();
};

#endif