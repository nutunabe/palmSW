#ifndef __BOSSPROJECTILE_H__
#define __BOSSPROJECTILE_H__
#include "cocos2d.h"

USING_NS_CC;

class BossProjectile : public cocos2d::Sprite
{
public:
	static BossProjectile* create(void);
	int getWidth();
	int getHeight();
	float getTop();
	float getBottom();
	float getLeft();
	float getRight();
	void update(float dt);

protected:
	SpriteFrameCache* spritecache;
	Animate* breakAnimate;
	Animate* fallAnimate;

	float velocityY;
	void initBossProjectile();
	float scale;
	int width;
	int height;
	float paddingTop;
	float paddingBottom;
	float paddingLeft;
	float paddingRight;

	Animate* initAnimation(char* name, int size, float dt);
};

#endif
