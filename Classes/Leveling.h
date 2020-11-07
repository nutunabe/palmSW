#ifndef __LEVELING_H__
#define __LEVELING_H__

#include <cocos2d.h>

USING_NS_CC;

class Leveling: public Sprite
{
public:
	static Leveling* create(void);
	Leveling();
	
	void Scrolling(Layer* layer);
private:
	Size visibleSize;
	Vec2 origin;
};

#endif // !__LEVELING_H__
