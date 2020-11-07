#include "KeyListener.h"

bool KeyListener::init(cocos2d::Layer* layer) {
	auto director = cocos2d::Director::getInstance();
	keyListener = cocos2d::EventListenerKeyboard::create();
	director->getOpenGLView()->setIMEKeyboardState(true);
	keyListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* ccevnt)
	{
		keyState[static_cast<int>(keyCode)] = true;
	};
	keyListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* ccevnt)
	{
		keyState[static_cast<int>(keyCode)] = false;
	};
	layer->getEventDispatcher()->addEventListenerWithFixedPriority(keyListener, 2);

	return true;
}
