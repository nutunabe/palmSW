#ifndef __GOBLIN__
#define __GOBLIN__

#include "ui/CocosGUI.h"
#include "Units/SpriteUnit.h"
#include "Units/Character.h"
#include "JsonParsing.h"

class Goblin : public SpriteUnit, public Character
{
public:
	int randFactor;
	static Goblin* create(void);
	void update();
	int getAttackAnimationIndex();
private:
	ui::LoadingBar* hpgoblin;

	JsonParsing js = JsonParsing();

	void initGoblin();
	void idle();
	void run();
	void attack();
	void takeHit();
	void die();
};

#endif