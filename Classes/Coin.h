#ifndef __COIN_H__
#define __COIN_H__

#include "Units/SpriteUnit.h"

USING_NS_CC;

#pragma once
class Coin : public SpriteUnit
{
public:
	static Coin* create(int x, int y, int width, int height);
	Size size;
	bool exist = false;
private:
	Size visibleSize;
	Vec2 origin;
	
	void Init();
};

#endif // !__COIN_H__