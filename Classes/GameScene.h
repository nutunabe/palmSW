#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Units/Player.h"
#include "Units/Enemies/Goblin.h"
#include "EnemyLogic.h"
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

USING_NS_CC;

class GameScene : public cocos2d::Scene
{
public:
	bool check = false;

	static cocos2d::Scene* createScene();

	virtual bool init();

	void goToMenu(Ref* Sender);

	void pause(Ref* Sender);

	CREATE_FUNC(GameScene);

	Sprite* mySprite;
	int groundLevel = 65;
	int levelLeftEdge = 0;
	int levelRightEdge = 6000;
private:
	Vector<Coin*> coins;
	Player* player;
	Vector<Goblin*> goblins;
	Leveling* level;
	KeyListener* keyListener;
	Platform* platforms[6];
	Platform* activePlatform;
	Shop* shop;
	HUD* hud;
	EnemyLogic* enemyLogic;
	Size visibleSize;
	Vec2 origin;
	DrawNode* playerNode;
	DrawNode* groundNode;
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
	void initCharacters();
	void initEnemies();
	void initEnvironment();
	void shopButton();
};

#endif
