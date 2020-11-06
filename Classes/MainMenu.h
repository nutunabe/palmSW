/*#pragma once
class MainMenu
{
};*/

#ifndef __MainMenu__
#define __MainMenu__

#include "cocos2d.h"

using namespace cocos2d;


class MainMenu : public Layer
{
private:
	void GoToGameScene( Ref *sender );

	void menuCloseCallback( Ref *sender );

public:
	static Scene* createScene();
	
	virtual bool init();

	CREATE_FUNC(MainMenu);
};


#endif // __MainMenu__