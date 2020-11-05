#ifndef __SPLASHSCREEN_H__
#define __SPLASHSCREEN_H__

#include "cocos2d.h"

class SplashScreen : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	void onEnter();

	void finishSplash();

	// implement the "static create()" method manually
	CREATE_FUNC(SplashScreen);
};

#endif