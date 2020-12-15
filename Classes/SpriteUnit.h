#ifndef __SPRITEUNIT_H__
#define __SPRITEUNIT_H__
#include "cocos2d.h"

USING_NS_CC;

class SpriteUnit : public cocos2d::Sprite
{
public:
	float velocityX;
	float velocityY;

	int getWidth();
	int getHeight();
	int getTop();
	int getBottom();
	int getLeft();
	int getRight();

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
	int paddingTop;
	int paddingBottom;
	int paddingLeft;
	int paddingRight;

	Animate* initAnimation(char* name, int size, float dt);
	Animate* initAnimation(char* name, int size, float dt, char* gg);
};

#endif
