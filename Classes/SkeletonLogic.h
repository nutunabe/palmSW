#include "Units/Enemies/Skeleton.h"
#include "Units/Player.h"
#include "Hud.h"

class SkeletonLogic
{
public:
	SkeletonLogic(Vector<Skeleton*> skeleton , Player* player, float groundLvl, HUD* hud);
	float ground;
	bool switched = false;
	bool switchedd = false;
	void chasePlayer();
	void attackPlayer(Skeleton* skeleton, int index);
private:
	Vector<Skeleton*> skeletons;
	Player* player;
	HUD* hud;
	clock_t start;
	clock_t end;
};

