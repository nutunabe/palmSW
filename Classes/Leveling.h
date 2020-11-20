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
	void parallax();
	void stopMoving();
	void setDirectionRight();
	void setDirectionLeft();
	
	bool isMoving = false;
private:
	//std::string levelString;
	Size visibleSize;
	Vec2 origin;
	Vector<Sprite*> background;
	Vector<Sprite*> background2;
	bool direction = 1;

	void update(float dt);
	void Init();
};

#endif // !__LEVELING_H__