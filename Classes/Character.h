#ifndef __CHARACTER_H__
#define __CHARACTER_H__
#include "cocos2d.h"
#include "States.h"

class Character
{
public:
	State stillState;
	State state;

	int getHealth();
	int getStamina();
	int getDamage();
	int getDamageRange();

protected:
	int health;
	int stamina;
	int damage;
	int damageRange;
};

#endif
