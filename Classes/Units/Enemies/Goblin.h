#ifndef __GOBLIN__
#define __GOBLIN__

#include "ui/CocosGUI.h"
#include "Units/SpriteUnit.h"
#include "Units/Character.h"

class Goblin : public SpriteUnit, public Character
{
public:
	static Goblin* create(void);
	void update();

private:
	void initGoblin();
	void idle();
	void run();
	void attack();
	void takeHit();
	void die();
	int health = 50;
	ui::LoadingBar* hpgoblin;

};

#endif