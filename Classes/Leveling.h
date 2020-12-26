#ifndef __LEVELING_H__
#define __LEVELING_H__

#include <cocos2d.h>
#include <iostream>
#include "Units/Player.h"
#include "Definitions.h"

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
	
	bool flag = false;
private:
	//std::string levelString;
	Size visibleSize;
	Vec2 origin;
	bool direction = 1;

	void update(float dt);
	void Init();
	JsonParsing js = JsonParsing();
};

#endif // !__LEVELING_H__