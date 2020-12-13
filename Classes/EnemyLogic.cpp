#include "EnemyLogic.h"

EnemyLogic::EnemyLogic(Vector<Goblin*> goblin, Player* player, float groundLvl) {
	this->player = player;
	this->goblins = goblin;
	this->ground = groundLvl;
}

void EnemyLogic::chasePlayer() {
	for (auto goblin : goblins) {
		if (goblin->state != gState::isDead &&
			goblin->state != gState::isDying) {
			Size visibleSize = Director::getInstance()->getVisibleSize();
				if (goblin->state != gState::isTakingHit) {
					if (goblin->getPositionX() > player->getPositionX() + 40 || goblin->getPositionX() < player->getPositionX() - 40) {
						if (goblin->state == gState::isAttacking) {
							goblin->stopAllActions();
						}
						if (goblin->getPositionX() < player->getPositionX() - 40) {		// left
							goblin->velocityX = goblin->velocityMax;
								goblin->setScaleX(abs(goblin->getScaleX()));
						}
						else if (goblin->getPositionX() > player->getPositionX() + 40) {	// right
							goblin->velocityX = -1 * goblin->velocityMax;
							goblin->setScaleX(abs(goblin->getScaleX()) * -1);
						}
						goblin->state = gState::isRunning;
					}
					if (player->state == State::isDead || player->minGroundY > ground) {
						goblin->velocityX = 0;
						goblin->state = goblin->stillState;
					}
				}
			if (goblin->getPositionX() < player->getPositionX() + 40 && goblin->getPositionX() > player->getPositionX() - 40 && player->minGroundY == ground) {								// attack
				if (goblin->state != gState::isAttacking) {
					goblin->stopAllActions();
					goblin->velocityX = 0;
					goblin->state = gState::isAttacking;
				}
			}
		}
	}
}

void EnemyLogic::attackPlayer() {

}
