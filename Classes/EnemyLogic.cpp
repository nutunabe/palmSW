#include "EnemyLogic.h"

EnemyLogic::EnemyLogic(Vector<Goblin*> goblin, Player* player, float groundLvl) {
	this->player = player;
	this->goblins = goblin;
	this->ground = groundLvl;
}

void EnemyLogic::chasePlayer() {
	for (auto goblin : goblins) {
		//clock_t start, end;
		//start = clock();
		//end = start + goblin->randFactor;
		//while (clock() < end) {
		//	// do nothing . . .
		//}
		if (goblin->state != State::isDead &&
			goblin->state != State::isDying) {
			Size visibleSize = Director::getInstance()->getVisibleSize();
			if (goblin->state != State::isTakingHit) {
				if (goblin->getPositionX() > player->getRight() || goblin->getPositionX() < player->getLeft()) {
					if (goblin->state == State::isAttacking) {
						goblin->stopAllActions();
					}
					if (goblin->getPositionX() < player->getLeft()) {		// left
						goblin->velocityX = goblin->getVelocityMax();
						goblin->setScaleX(abs(goblin->getScaleX()));
					}
					else if (goblin->getPositionX() > player->getRight()) {	// right
						goblin->velocityX = -1 * goblin->getVelocityMax();
						goblin->setScaleX(abs(goblin->getScaleX()) * -1);
					}
					goblin->state = State::isRunning;
				}
				if (player->state == State::isDead || player->minGroundY > ground) {
					goblin->velocityX = 0;
					if (goblin->state == State::isAttacking) {
						goblin->stopAllActions();
					}
					goblin->state = goblin->stillState;
				}
			}
			if (goblin->getPositionX() < player->getRight() && goblin->getPositionX() > player->getLeft() && player->minGroundY == ground) {								// attack
				attackPlayer();
			}
		}
	}
}

void EnemyLogic::attackPlayer() {
	for (auto goblin : goblins) {
		if (goblin->state != State::isAttacking) {
			goblin->stopAllActions();
			goblin->velocityX = 0;
			goblin->state = State::isAttacking;
			player->takeDamage(goblin->getDamage());
		}
	}
}
