#ifndef __BOSSARENA_H__
#define __BOSSARENA_H__

#include "cocos2d.h"

#include "Units/Enemies/Boss.h"
#include "BossLogic.h"
#include "BossProjectile.h"

class BossArena : public cocos2d::Scene
{
private:
	Boss* boss;
	BossLogic* bossLogic;
	Vector<BossProjectile*> bossproj;
};

#endif
