#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"

USING_NS_CC;

class Player : public cocos2d::Sprite {
public:
	Animate* idleAnimate;
	Animate* readyAnimate;
	Animate* runAnimate;

	static Player* create(void);
	void run(std::string direction);
	void idle();

private:
	bool is_moving;
	std::string direction;

	void initPlayer();
	void listenKeyboard();
	void update(float dt);
};

#endif