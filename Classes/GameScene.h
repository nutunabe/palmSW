#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Player.h"
#include "Leveling.h"
#include "KeyListener.h"
#include "MainMenu.h"
#include "Platform.h"
#include "HUD.h"

using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	//void menuCloseCallback(Ref* pSender);

	void goToMenu(Ref* Sender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	Sprite *mySprite;
	int groundLevel = 50;
private:
	Player* player;
	Leveling* level;
	KeyListener* keyListener;
	Platform* platforms[6];
	Platform* activePlatform;
	HUD* hud;
	//PhysicsWorld* sceneWorld;

	//int keys[12] = { 28,26,29,27,146,124,142,127,129,59,77,78 };
	int keys[8] = { 26,27,124,127,129,59,77,78 };

	void keyCheck();
	void whatKey(bool* keyState);
	void update(float dt);
	void checkActivePlatform();
	//void setPhysicsWorld(PhysicsWorld* world) { sceneWorld = world; }
};

#endif
