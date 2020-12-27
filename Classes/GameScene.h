#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Units/Player.h"
#include "Units/Enemies/Goblin.h"
#include "Units/Enemies/Skeleton.h"
#include "EnemyLogic.h"
#include "SkeletonLogic.h"
#include "Leveling.h"
#include "KeyListener.h"
#include "MainMenu.h"
#include "Platform.h"
#include "HUD.h"
#include "Coin.h"
#include "GSPause.h"
#include "Shop.h"
#include "PopupDelegates.h"
#include "ui/CocosGUI.h"
#include "Definitions.h"
#include "Units/Enemies/Boss.h"
#include "BossLogic.h"
#include "BossProjectile.h"

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	bool check = false;
	bool bossTrigger = false;

	static cocos2d::Scene* createScene();

	virtual bool init();

	void goToMenu(Ref* Sender);

	void pause(Ref* Sender);

	void resumeScene(Ref* Sender);

	CREATE_FUNC(GameScene);

	Sprite* mySprite;
	int groundLevel = 65;
	int levelLeftEdge = 0;
	int levelRightEdge = 8000;
private:
	Vector<Coin*> coins;
	Player* player;
	Vector<Goblin*> goblins;
	Vector<Skeleton*> skeletons;
	Leveling* level;
	KeyListener* keyListener;
	Vector<Platform*> platforms;
	Platform* activePlatform;
	Shop* shop;
	HUD* hud;
	EnemyLogic* enemyLogic;
	SkeletonLogic* skeletonLogic;
	Size visibleSize;
	Vec2 origin;
	DrawNode* playerNode;
	DrawNode* groundNode;
	DrawNode* bossNode;
	Boss* boss;
	BossLogic* bossLogic;
	Vector<BossProjectile*> bossproj;

	int keys[8] = { 26,27,124,127,129,59,77,78 };
	bool keyState[256];
	bool keyReleased[256];
	bool keyPressed[256];

	void listenKeyboard();
	void keyCheck();
	void whatKey(bool* keyState);
	void update(float dt);
	void checkActivePlatform();
	void checkTakeCoin();
	void checkShop(Ref* sender);
	void checkCollision();
	void attackGoblin(Goblin* goblin, int index);
	void attackSkeleton(Skeleton* skeleton, int index);
	void initCharacters();
	void initEnemies();
	void initEnvironment();
	void shopButton();
};

#endif
