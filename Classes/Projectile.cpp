#include "Projectile.h"

USING_NS_CC;

Projectile* Projectile::create() {
	Projectile* projectile = new Projectile();
	if (projectile->init()) {
	
	}
	return NULL;
}