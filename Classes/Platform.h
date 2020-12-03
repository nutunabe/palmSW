#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include<cocos2d.h>

USING_NS_CC;

#pragma once
class Platform : public Sprite
{
public:
	static Platform* create(int x, int y, int width, int height);
	Platform();
	Point coordinate;
	Size size;
	bool direction = 1;
	void parallax();
	void setDirectionRight();
	void setDirectionLeft();

private:
	Size visibleSize;
	Vec2 origin;

	void Init();
};

#endif // !__PLATFORM_H__