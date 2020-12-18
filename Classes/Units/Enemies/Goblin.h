#ifndef __GOBLIN__
#define __GOBLIN__

#include "ui/CocosGUI.h"
#include "Units/SpriteUnit.h"
#include "Units/Character.h"

class Goblin : public SpriteUnit, public Character
{
public:
	int randFactor;
	static Goblin* create(void);
	void update();

private:
	ui::LoadingBar* hpgoblin;

	void initGoblin();
	void idle();
	void run();
	void attack();
	void takeHit();
	void die();
};

#endif