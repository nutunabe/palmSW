#include "Units/Enemies/Goblin.h"
#include "Units/Player.h"
#include "Hud.h"

class EnemyLogic
{
public:
	EnemyLogic(Vector<Goblin*> goblin, Player* player, float groundLvl, HUD* hud);
	float ground;
	bool switched = false;
	bool switchedd = false;
	void chasePlayer(float dt);
	void attackPlayer(Goblin* goblin, int index, float dt);
private:
	Vector<Goblin*> goblins;
	Player* player;
	HUD* hud;
	float start = -1;
	float end;
};
