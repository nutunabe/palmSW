#include "Units/Enemies/Skeleton.h"
#include "Units/Player.h"
#include "Hud.h"

class SkeletonLogic
{
public:
	SkeletonLogic(Vector<Skeleton*> skeleton, Player* player, float groundLvl, HUD* hud);
	float ground;
	bool switched = false;
	bool switchedd = false;
	void chasePlayer(float dt);
	void attackPlayer(Skeleton* skeleton, int index, float dt);
private:
	Vector<Skeleton*> skeletons;
	Player* player;
	HUD* hud;
	float start = 0;
	float end;
};

