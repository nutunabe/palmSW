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
	isFlying,
	isFalling,
	isTakingHit,
	isDying,
	isDead
};

class Player : public cocos2d::Sprite {
public:
	Animate* idleAnimate;
	Animate* readyAnimate;
	Animate* runAnimate;
	Animate* attackAnimate;

	State state = State::isReady;
	int maxVelocity = 5;
	int velocity;

	void update();
	static Player* create(void);

private:
	void initPlayer();
	void idle();
	void ready();
	void run();
	void attack();
	void jump();
	void takeHit();
	void Die();
	//void borderStuck();
};

#endif