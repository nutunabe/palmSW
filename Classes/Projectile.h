#ifndef __PROJECTILE__
#define __PROJECTILE__

#include "Units/SpriteUnit.h"

class Projectile : public SpriteUnit
{
public:
	static Projectile* create(void);
	void update();
private:
};

#endif

