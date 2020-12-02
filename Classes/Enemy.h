#ifndef __ENEMY_H__
#define __ENEMY_H__

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

class Enemy : public cocos2d::Sprite {
public:
	State stillState = State::isReady;
	State state = stillState;
	float velocityMax = 5;
	float velocityX;
	float velocityY = 0;
	int minGroundY;

	void update();
	static Enemy* create(char* name, float health, float damage);

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
	void initEnemy(char* name, float health, float damage);
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