#pragma once
#ifndef __GSPAUSE_H__

#include "cocos2d.h"
#include "GameScene.h"
#include <ui/CocosGUI.h>

USING_NS_CC;

class GSPause : public Layer
{
private:
	void createShieldLayer();


public:
	CREATE_FUNC(GSPause);
	static Layer* addLayer();
};

#endif // !__GSPAUSE_H__