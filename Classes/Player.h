#ifndef _PLAYER_
#define _PLAYER_

#include "cocos2d.h"

class Player : public cocos2d::Sprite {
public:
	static Player* create(void);

private:
	bool is_moving;
	std::string direction;

	void initPlayer();
	void listenKeyboard();
	void update(float dt);
};

#endif