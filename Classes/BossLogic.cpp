#include "BossLogic.h"

BossLogic::BossLogic(Boss* boss, Player* player, HUD* hud) {
	this->player = player;
	this->boss = boss;
	this->hud = hud;
}

void BossLogic::update() {
	//chasePlayer();
	sturmTiger();
}

void BossLogic::sturmTiger() {
	boss->mode = FightMode::sturmtiger;
	boss->state = State::isAttacking;
}

void BossLogic::chasePlayer() {
		if (boss->state != State::isDead &&
			boss->state != State::isDying &&
			player->state != State::isDead &&
			player->state != State::isDying) {
			if (boss->state != State::isTakingHit) {
				if (boss->getPositionX() > player->getRight() || boss->getPositionX() < player->getLeft()) {
					if (boss->state == State::isAttacking) {
						boss->stopAllActions();
					}
					if (boss->getPositionX() < player->getLeft()) {		// left
						boss->velocityX = boss->getVelocityMax();
						boss->setScaleX(abs(boss->getScaleX()));
					}
					else if (boss->getPositionX() > player->getRight()) {	// right
						boss->velocityX = -1 * boss->getVelocityMax();
						boss->setScaleX(abs(boss->getScaleX()) * -1);
					}
					boss->state = State::isRunning;
				}
				if (player->state == State::isDead) {
					boss->velocityX = 0;
					if (boss->state == State::isAttacking) {
						boss->stopAllActions();
					}
					boss->state = boss->stillState;
				}
			}
			if (boss->getPositionX() < player->getRight() && boss->getPositionX() > player->getLeft()) {
				attackPlayer(boss, boss->getAttackAnimationIndex()); //attention
			}
		}
}

void BossLogic::attackPlayer(Boss* boss, int index) {
	if (boss->state != State::isAttacking && switched) {
		boss->stopAllActions();
		boss->velocityX = 0;
		boss->state = State::isAttacking;
	}

	if (clock() >= end) {
		start = clock();
		end = start + 2000;
		switched = true;
	}
	else {
		switched = false;
	}

	if (boss->state == State::isAttacking) {
		if (player->state != State::isAttacking &&
			player->state != State::isTakingHit &&
			index == 6) {
			player->stopAllActions();
			player->velocityX = 0;
			player->state = State::isTakingHit;
			player->takeDamage(boss->getDamage());
			hud->getHit(boss->getDamage());
		}
	}
}
