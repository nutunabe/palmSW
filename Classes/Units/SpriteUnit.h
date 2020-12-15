#ifndef __SPRITEUNIT_H__
#define __SPRITEUNIT_H__
#include "cocos2d.h"

USING_NS_CC;

class SpriteUnit : public cocos2d::Sprite
{
public:
	int getWidth();
	int getHeight();
	float getTop();
	float getBottom();
	float getLeft();
	float getRight();

	void update();

protected:
	SpriteFrameCache* spritecache;
	Animate* idleAnimate;
	Animate* readyAnimate;
	Animate* runAnimate;
	Animate* attackAnimate;
	Animate* takeHitAnimate;
	Animate* jumpAnimate;
	Animate* deathAnimate;
	Animate* deadAnimate;

	float scale;
	int width;
	int height;
	float paddingTop;
	float paddingBottom;
	float paddingLeft;
	float paddingRight;

	Animate* initAnimation(char* name, int size, float dt);
	Animate* initAnimation(char* name, int size, float dt, char* gg);
};

#endif
