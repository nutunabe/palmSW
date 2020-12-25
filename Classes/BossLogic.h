#include "Units/Enemies/Boss.h"
#include "Units/Player.h"
#include "Hud.h"

class BossLogic
{
public:
	BossLogic(Boss* boss, Player* player, HUD* hud);
	bool switched = false;
	bool switchedd = false;
	void chasePlayer();
	void attackPlayer(Boss* boss, int index);
	void update();
private:
	Boss* boss;
	Player* player;
	HUD* hud;
	clock_t start;
	clock_t end;
};
