#ifndef __DEATHS_SCREEN__H__
#define __DEATHS_SCREEN__H__

#include "cocos2d.h"

using namespace cocos2d;

class DeathScreen : public Scene
{
public:

	static Scene* createScene();

    void menuCloseCallback(Ref* pSender);

	virtual bool init();
	
	void onEnter();

	CREATE_FUNC(DeathScreen);

	void GoToMainMenu(float dt);


private:

};

#endif