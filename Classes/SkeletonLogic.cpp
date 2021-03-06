#include "SkeletonLogic.h"

SkeletonLogic::SkeletonLogic(Vector<Skeleton*> skeleton, Player* player, float groundLvl, HUD* hud) {
	this->player = player;
	this->skeletons = skeleton;
	this->ground = groundLvl;
	this->hud = hud;
}

void SkeletonLogic::chasePlayer(float dt) {
	for (auto skeleton : skeletons) {
		if (skeleton->state != State::isDead &&
			skeleton->state != State::isDying &&
			player->state != State::isDead &&
			player->state != State::isDying) {
			if (skeleton->state != State::isTakingHit) {
				if (skeleton->getPositionX() > player->getRight() || skeleton->getPositionX() < player->getLeft()) {
					if (skeleton->state == State::isAttacking) {
						skeleton->stopAllActions();
					}
					if (skeleton->getPositionX() < player->getLeft()) {		// left
						skeleton->velocityX = skeleton->getVelocityMax();
						skeleton->setScaleX(abs(skeleton->getScaleX()));
					}
					else if (skeleton->getPositionX() > player->getRight()) {	// right
						skeleton->velocityX = -1 * skeleton->getVelocityMax();
						skeleton->setScaleX(abs(skeleton->getScaleX()) * -1);
					}
					skeleton->state = State::isRunning;
				}
				if (player->state == State::isDead || player->minGroundY != skeleton->minGroundY) {
					skeleton->velocityX = 0;
					if (skeleton->state == State::isAttacking) {
						skeleton->stopAllActions();
					}
					skeleton->state = skeleton->stillState;
				}
			}
			if (skeleton->getPositionX() <= player->getRight() && skeleton->getPositionX() >= player->getLeft() && player->minGroundY == skeleton->minGroundY) {
				skeleton->velocityX = 0;
				attackPlayer(skeleton, skeleton->getAttackAnimationIndex(), dt);
			}
			else {
				skeleton->attackTime = -1;
			}
		}
	}
}

void SkeletonLogic::attackPlayer(Skeleton* skeleton, int index, float dt) {
	if (skeleton->state != State::isAttacking && switched) {
		skeleton->stopAllActions();
		skeleton->velocityX = 0;
		skeleton->state = State::isAttacking;
	}

	if (skeleton->attackTime >= 2.0 || skeleton->attackTime == -1) {
		skeleton->attackTime = 0;
		switched = true;
	}
	else {
		skeleton->attackTime += dt;
		switched = false;
	}

	if (skeleton->state == State::isAttacking) {
		if (player->state != State::isAttacking &&
			player->state != State::isTakingHit &&
			index == 5) {
			player->stopAllActions();
			player->velocityX = 0;
			player->state = State::isTakingHit;
			player->takeDamage(skeleton->getDamage());
		}
	}
}
