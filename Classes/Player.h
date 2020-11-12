#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite {
public:
	Animate* idleAnimate;
	Animate* readyAnimate;
	Animate* runAnimate;
	Animate* attackAnimate;

	static Player* create(void);
	void run(std::string direction);
	void idle();
	void attack();

private:
	bool is_moving;
	bool is_idle;
	bool is_attackPress;
	bool is_attacking;
	std::string direction;

	void initPlayer();
	void listenKeyboard();
	void update(float dt);
};

#endif