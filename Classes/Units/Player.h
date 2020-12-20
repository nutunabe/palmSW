#ifndef __PLAYER__
#define __PLAYER__

#include "Units/SpriteUnit.h"
#include "Units/Character.h"

class Player : public SpriteUnit, public Character
{
public:
	static Player* create(void);
	void update();
	int getAttackAnimationIndex();

private:
	void initPlayer();
	void idle();
	void ready();
	void run();
	void attack();
	void jump();
	void takeHit();
	void die();
};

#endif