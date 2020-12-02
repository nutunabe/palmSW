#ifndef __COIN_H__
#define __COIN_H__

#include<cocos2d.h>

USING_NS_CC;

#pragma once
class Coin : public Sprite
{
public:
	static Coin* create(int x, int y, int width, int height);
	Point coordinate;
	Size size;
	bool exist = false;
private:
	Size visibleSize;
	Vec2 origin;
	
	void Init();
};

#endif // !__COIN_H__