#include "Goblin.h"
#include "Player.h"

class EnemyLogic
{
public:
	EnemyLogic(Goblin* goblin, Player* player);
	bool switched = false;
	bool switchedd = false;
	void chasePlayer();
	void attackPlayer();
private:
	Goblin* goblin; 
	Player* player;
};

