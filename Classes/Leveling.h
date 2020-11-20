#ifndef __LEVELING_H__
#define __LEVELING_H__

#include <cocos2d.h>
#include <iostream>
#include "Player.h"

USING_NS_CC;

class Leveling: public Sprite
{
public:
	static Leveling* create(void);
	Leveling();
	
private:
	//std::string levelString;
	Size visibleSize;
	Vec2 origin;
	Vector<Sprite*> background;

	void update(float dt);
	void Init();
	void checkMoving();
};

#endif // !__LEVELING_H__