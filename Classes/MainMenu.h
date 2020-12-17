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
#include "include/rapidjson/document.h"
#include "include/rapidjson/error/en.h"
#include <include/rapidjson/istreamwrapper.h>
#include <include/rapidjson/ostreamwrapper.h>
#include "include/rapidjson/writer.h"
#include <iostream>
#include <fstream>

using namespace cocos2d;


class MainMenu : public Layer
{
private:
	void GoToGameScene( Ref *sender );

	void menuCloseCallback( Ref *sender );

	void showSettings( Ref *sender);

	void showMenu(Ref *sender);

	void showMainMenu();

	void sliderEvent(Ref* sender, ui::Slider::EventType type);
	
	float musicVolume;

	int musicID;

	ui::Slider* slider;

	rapidjson::Document doc;
public:
	static Scene* createScene();
	

	virtual bool init();

	CREATE_FUNC(MainMenu);


	Size visibleSize;
	Vec2 origin;
};


#endif // __MainMenu__