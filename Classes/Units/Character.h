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
	float attackTime;

	int getHealth();
	void setHealth(int hp);
	int getStamina();
	void setStamina(int st);
	int getDamage();
	int getDamageRange();
	void takeDamage(int damage);
	int getVelocityMax();

	void upgradeDamage(float dmg);

protected:
	float health;
	float stamina;
	int damage;
	int damageRange;
	float velocityMax;
};

#endif
