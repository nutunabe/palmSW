#include "Character.h"

int Character::getHealth() {
	return health;
}

void Character::setHealth(int hp) {
	health += hp;
}

int Character::getStamina() {
	return stamina;
}

int Character::getDamage() {
	return damage;
}

int Character::getDamageRange() {
	return damageRange;
}

void Character::takeDamage(int damage) {
	health -= damage;
}

int Character::getVelocityMax() {
	return velocityMax;
}