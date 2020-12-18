#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "cocos2d.h"
#include "States.h"

class Character
{
public:
	State stillState;
	State state;

	float velocityX;
	float velocityY;
	int minGroundY;

	int getHealth();
	void setHealth(int hp);
	int getStamina();
	int getDamage();
	int getDamageRange();
	void takeDamage(int damage);
	int getVelocityMax();

protected:
	int health;
	int stamina;
	int damage;
	int damageRange;
	int velocityMax;
};

#endif
