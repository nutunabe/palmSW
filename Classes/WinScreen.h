#ifndef __WIN_SCREEN__H__
#define __WIN_SCREEN__H__

#include "cocos2d.h"

using namespace cocos2d;

class WinScreen : public Scene
{
public:

	static Scene* createScene();

	void menuCloseCallback(Ref* pSender);

	virtual bool init();

	void onEnter();

	CREATE_FUNC(WinScreen);

	void GoToMainMenu(float dt);


private:

};

#endif
