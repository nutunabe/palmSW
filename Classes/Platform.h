#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include<cocos2d.h>

USING_NS_CC;

#pragma once
class Platform : public Sprite
{
public:
	static Platform* create(void);
	Platform();
private:
	Point coordinate;
	Size size;
	Size visibleSize;
	Vec2 origin;


	void Init();
	//void update(float dt);
};

#endif // !__PLATFORM_H__