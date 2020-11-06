#ifndef __GAMESCENE_H__
#define __GAMESCENE_H__

#include "cocos2d.h"
#include "Player.h"

using namespace cocos2d;

class GameScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	// a selector callback
	void menuCloseCallback(Ref* pSender);

	void goToMenu(Ref* Sender);

	// implement the "static create()" method manually
	CREATE_FUNC(GameScene);

	Sprite *mySprite;
private:
	Player* player;
};

#endif
