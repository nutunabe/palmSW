#include "Units/Enemies/Boss.h"
#include "Units/Player.h"
#include "Hud.h"
#include "BossProjectile.h"

class BossLogic
{
public:
	BossLogic(Boss* boss, Player* player, HUD* hud, Vector<BossProjectile*> bossproj);
	bool switched = false;
	bool switchedd = false;
	void chasePlayer(float dt);
	void sturmTiger(float dt);
	void bitePlayer(Boss* boss, int index, float dt);
	void attackPlayer(Boss* boss, int index, float dt);
	void update(float dt);
private:
	Vector<BossProjectile*> bossproj;
	Boss* boss;
	Player* player;
	HUD* hud;
	float start = 0;
	float end = 0;
};
