#include "BossLogic.h"

BossLogic::BossLogic(Boss* boss, Player* player, HUD* hud, Vector<BossProjectile*> bossproj) {
	this->player = player;
	this->boss = boss;
	this->hud = hud;
	this->bossproj = bossproj;
	boss->mode = FightMode::punch;
}

void BossLogic::update(float dt) {
	if (player->getPositionX() >= 5250 && player->getPositionX() <= 6000) {
		if (updateTime > 10.0 && updateTime < 10.1) {
			boss->stopAllActions();
			boss->mode = FightMode::sturmtiger;
		}
		if (updateTime > 20.0 && updateTime < 20.1) {
			boss->stopAllActions();
			boss->mode = FightMode::bite;
			updateTime = 0;
		}

		switch (boss->mode) {
		case FightMode::punch:
		case FightMode::bite:
			chasePlayer(dt);
			break;
		case FightMode::sturmtiger:
			sturmTiger(dt);
			break;
		}

		updateTime += dt;
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
	switch (boss->mode) {
	case FightMode::punch:
		if (boss->getPositionX() < player->getRight() && boss->getPositionX() > player->getLeft()) {
			attackPlayer(boss, boss->getAttackAnimationIndex(), dt);
		}
		else {
			attackTime = -1;
		}
		break;
	case FightMode::bite:
		if (boss->getPositionX() < player->getRight() && boss->getPositionX() > player->getLeft()) {
			bitePlayer(boss, boss->getAttackAnimationIndex(), dt);
		}
		else {
			attackTime = -1;
		}
		break;
	}

}

void BossLogic::attackPlayer(Boss* boss, int index, float dt) {
	if (boss->state != State::isAttacking && switched) {
		boss->stopAllActions();
		boss->velocityX = 0;
		boss->state = State::isAttacking;
	}

	if (attackTime >= 2.0 || attackTime==-1) {
		attackTime = 0;
		switched = true;
	}
	else {
		attackTime += dt;
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
		}
	}
}

void BossLogic::bitePlayer(Boss* boss, int index, float dt) {
	if (boss->state != State::isAttacking && switched) {
		boss->stopAllActions();
		boss->velocityX = 0;
		boss->state = State::isAttacking;
	}

	if (attackTime >= 2.0 || attackTime == -1) {
		attackTime = 0;
		switched = true;
	}
	else {
		attackTime += dt;
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
		}
	}
}

void BossLogic::sturmTiger(float dt) {
	boss->velocityX = 0;
	boss->mode = FightMode::sturmtiger;
	boss->state = State::isAttacking;

	if (attackTime >= 1.0 && attackTime < 1.1) {
		bossproj.at(0)->setPositionX(player->getPositionX());
	}
	if (attackTime >= 1.5 && attackTime < 1.6) {
		bossproj.at(1)->setPositionX(player->getPositionX());
	}
	if (attackTime >= 2.0 && attackTime < 2.1) {
		bossproj.at(2)->setPositionX(player->getPositionX());
	}
	if (attackTime >= 2.5 && attackTime < 2.6) {
		bossproj.at(3)->setPositionX(player->getPositionX());
	}
	if (attackTime >= 3.0 && attackTime < 3.1) {
		bossproj.at(4)->setPositionX(player->getPositionX());
	}
	if (attackTime >= 3.5 && attackTime < 3.6) {
		bossproj.at(5)->setPositionX(player->getPositionX());
	}
	if (attackTime >= 4.0 && attackTime < 4.1) {
		bossproj.at(6)->setPositionX(player->getPositionX());
	}
	if (attackTime >= 4.5) {
		attackTime = 0;
		boss->stopAllActions();
		boss->mode = FightMode::punch;
	}
	attackTime += dt;
}
