#include "Goblin.h"
#include "Player.h"

class EnemyLogic
{
public:
	EnemyLogic(Goblin* goblin, Player* player, float groundLvl);
	float ground;
	bool switched = false;
	bool switchedd = false;
	void chasePlayer();
	void attackPlayer();
private:
	Goblin* goblin; 
	Player* player;
};

