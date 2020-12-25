#ifndef __BOSS__
#define __BOSS__

#include "ui/CocosGUI.h"
#include "Units/SpriteUnit.h"
#include "Units/Character.h"

enum class FightMode {
	bite,
	punch,
	sturmtiger
};

class Boss : public SpriteUnit, public Character
{
public:
	int randFactor;
	static Boss* create(void);
	void update();
	int getAttackAnimationIndex();
	FightMode mode;

private:
	ui::LoadingBar* hpboss;

	Animate* attack2Animate;
	Animate* attack3Animate;
	void initBoss();
	void idle();
	void run();
	void attack1();
	void attack2();
	void attack3();
	void takeHit();
	void die();
};

#endif