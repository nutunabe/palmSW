#include "EnemyLogic.h"

EnemyLogic::EnemyLogic(Vector<Goblin*> goblin, Player* player, float groundLvl, HUD* hud) {
	this->player = player;
	this->goblins = goblin;
	this->ground = groundLvl;
	this->hud = hud;
}

void EnemyLogic::chasePlayer() {
	for (auto goblin : goblins) {
		if (goblin->state != State::isDead &&
			goblin->state != State::isDying &&
			player->state != State::isDead &&
			player->state != State::isDying) {
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
			if (goblin->getPositionX() < player->getRight() && goblin->getPositionX() > player->getLeft() && player->minGroundY == ground) {
				attackPlayer(goblin, goblin->getAttackAnimationIndex());
			}
		}
	}
}

void EnemyLogic::attackPlayer(Goblin* goblin, int index) {
	if (goblin->state != State::isAttacking && switched) {
		goblin->stopAllActions();
		goblin->velocityX = 0;
		goblin->state = State::isAttacking;
	}

	if (clock() >= end) {
		start = clock();
		end = start + 2000;
		switched = true;
	}
	else {
		switched = false;
	}

	if (goblin->state == State::isAttacking) {
		if (player->state != State::isAttacking &&
			player->state != State::isTakingHit &&
			index == 6) {
			player->stopAllActions();
			player->velocityX = 0;
			player->state = State::isTakingHit;
			player->takeDamage(goblin->getDamage()); 
			hud->getHit(goblin->getDamage());
		}
	}
}
