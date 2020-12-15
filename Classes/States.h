#ifndef __STATES_H__
#define __STATES_H__

enum class State {
	isIdle,
	isReady,
	isRunning,
	isAttacking,
	isJumping,
	isTakingHit,
	isDying,
	isDead
};

#endif
