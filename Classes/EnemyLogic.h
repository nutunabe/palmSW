#include "Units/Enemies/Goblin.h"
#include "Units/Player.h"

class EnemyLogic
{
public:
	EnemyLogic(Vector<Goblin*> goblin, Player* player, float groundLvl);
	float ground;
	bool switched = false;
	bool switchedd = false;
	void chasePlayer();
	void attackPlayer();
private:
	Vector<Goblin*> goblins; 
	Player* player;
	clock_t start;
	clock_t end;
};

