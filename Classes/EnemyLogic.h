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
	void chasePlayer();
	void attackPlayer(Goblin* goblin, int index);
private:
	Vector<Goblin*> goblins; 
	Player* player;
	HUD* hud;
	clock_t start;
	clock_t end;
};
