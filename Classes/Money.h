#ifndef __MONEY_H__
#define __MONEY_H__

#include<cocos2d.h>

USING_NS_CC;

#pragma once
class Money : public Sprite
{
public:
	static Money* create(int x, int y, int width, int height);
	Point coordinate;
	Size size;
private:
	Size visibleSize;
	Vec2 origin;


	void Init();
};

#endif // !__MONEY_H__