#include "KeyListener.h"

KeyListener* KeyListener::create(cocos2d::EventDispatcher* dispatcher)
{
	KeyListener* kl = new KeyListener();
	kl->init(dispatcher);
	return kl;
}

bool KeyListener::init(cocos2d::EventDispatcher* dispatcher) {
	auto director = cocos2d::Director::getInstance();
	keyListener = cocos2d::EventListenerKeyboard::create();
	director->getOpenGLView()->setIMEKeyboardState(true);
	keyListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* ccevnt)
	{
		keyState[static_cast<int>(keyCode)] = true;
		keyPressed[static_cast<int>(keyCode)] = true;
		//char str[100];
		//sprintf(str,"%d", static_cast<int>(keyCode));
		//CCLOG(str);
	};
	keyListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* ccevnt)
	{
		keyState[static_cast<int>(keyCode)] = false;
		keyReleased[static_cast<int>(keyCode)] = true;
	};
	dispatcher->addEventListenerWithFixedPriority(keyListener, 1);
	return true;
}
