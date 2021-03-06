/*#pragma once
class MainMenu
{
};*/

#ifndef __MainMenu__
#define __MainMenu__

#include "cocos2d.h"
#include "GameScene.h"
#include "AudioEngine.h"
#include <ui/CocosGUI.h>
#include "Definitions.h"
#include "JsonParsing.h"

using namespace cocos2d;


class MainMenu : public Layer
{
private:
	void GoToGameScene( Ref *sender );

	void menuCloseCallback( Ref *sender );

	void showMenu(Ref *sender);

	void showSettings(Ref* sender);

	void showMainMenu();

	void sliderEvent(Ref* sender, ui::Slider::EventType type);
	
	JsonParsing js = JsonParsing();

	float musicVolume;
	float soundfxVolume;

	int musicID;
	int soundfxID;

	ui::Slider* slider;
	ui::Slider* sliderFX;

public:
	static Scene* createScene();

	virtual bool init();

	CREATE_FUNC(MainMenu);


	Size visibleSize;
	Vec2 origin;
};


#endif // __MainMenu__