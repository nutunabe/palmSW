#include "BossLogic.h"

BossLogic::BossLogic(Boss* boss, Player* player, HUD* hud, Vector<BossProjectile*> bossproj) {
	this->player = player;
	this->boss = boss;
	this->hud = hud;
	this->bossproj = bossproj;
	boss->mode = FightMode::sturmtiger;
}

void BossLogic::update(float dt) {
	switch (boss->mode) {
	case FightMode::punch:
		chasePlayer(dt);
		break;
	case FightMode::bite:
		bitePlayer(boss, boss->getAttackAnimationIndex());
		break;
	case FightMode::sturmtiger:
		sturmTiger(dt);
		break;
	}
}

void BossLogic::chasePlayer(float dt) {
	if (boss->state != State::isDead &&
		boss->state != State::isDying &&
		player->state != State::isDead &&
		player->state != State::isDying) {
		if (boss->state != State::isTakingHit) {
			if (boss->getPositionX() > player->getRight() || boss->getPositionX() < player->getLeft()) {
				if (boss->state == State::isAttacking) {
					boss->stopAllActions();
				}
				if (boss->getPositionX() < player->getLeft()) {			// left
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

	}
	if (boss->getPositionX() < player->getRight() && boss->getPositionX() > player->getLeft()) {
		attackPlayer(boss, boss->getAttackAnimationIndex(), dt);
	}
}

void BossLogic::attackPlayer(Boss* boss, int index, float dt) {
	if (boss->state != State::isAttacking && switched) {
		boss->stopAllActions();
		boss->velocityX = 0;
		boss->state = State::isAttacking;
	}

	if (start >= 2.0) {
		start = 0;
		switched = true;
	}
	else {
		start += dt;
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

void BossLogic::bitePlayer(Boss* boss, int index) {

	// . . .
	boss->state = State::isAttacking;
}

void BossLogic::sturmTiger(float dt) {
	boss->mode = FightMode::sturmtiger;
	boss->state = State::isAttacking;

	if (start >= 0.5 && start < 0.6) {
		bossproj.at(0)->setPositionX(player->getPositionX());
	}
	if (start >= 1.0 && start < 1.1) {
		bossproj.at(1)->setPositionX(player->getPositionX());
	}
	if (start >= 1.5 && start < 1.6) {
		bossproj.at(2)->setPositionX(player->getPositionX());
	}
	if (start >= 2.0 && start < 2.1) {
		bossproj.at(3)->setPositionX(player->getPositionX());
	}
	if (start >= 2.5 && start < 2.6) {
		bossproj.at(4)->setPositionX(player->getPositionX());
	}
	if (start >= 3.0 && start < 3.1) {
		bossproj.at(5)->setPositionX(player->getPositionX());
	}
	if (start >= 3.5 && start < 3.6) {
		bossproj.at(6)->setPositionX(player->getPositionX());
	}
	start += dt;

}
