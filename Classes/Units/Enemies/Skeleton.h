#ifndef __SKELETON__
#define __SKELETON__

#include "ui/CocosGUI.h"
#include "Units/SpriteUnit.h"
#include "Units/Character.h"
#include "JsonParsing.h"

class Skeleton : public SpriteUnit, public Character
{
public:
	int randFactor;
	static Skeleton* create(void);
	void update();
	int getAttackAnimationIndex();

private:
	ui::LoadingBar* hpskeleton;
	JsonParsing js = JsonParsing();

	void initSkeleton();
	void idle();
	void run();
	void attack();
	void takeHit();
	void die();
};

#endif
