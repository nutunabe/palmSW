#ifndef __KEY_LISTENER_H__
#define __KEY_LISTENER_H__

#include "cocos2d.h"

// temporary class only for win32
class KeyListener
{
public:
	static KeyListener* create(cocos2d::EventDispatcher* dispatcher);

	virtual bool init(cocos2d::EventDispatcher* dispatcher);

	cocos2d::EventListenerKeyboard* keyListener;
	bool keyState[256];
};

#endif
