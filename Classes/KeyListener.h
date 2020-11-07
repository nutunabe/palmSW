#ifndef __KEY_LISTENER_H__
#define __KEY_LISTENER_H__

#include "cocos2d.h"

// temporary class only for win32
class KeyListener
{
public:
	virtual bool init(cocos2d::Layer* layer);

	cocos2d::EventListenerKeyboard* keyListener;
	bool keyState[256];
};

#endif
