#include "Coin.h"

USING_NS_CC;

Coin* Coin::create(int x, int y, int width, int height) {
	Coin* coin = new Coin();

	if (coin->init()) {
		coin->setPositionX(x);
		coin->setPositionY(y);
		coin->size.width = width;
		coin->size.height = height;
		coin->Init();

		return coin;
	}
	CC_SAFE_DELETE(coin);
	return NULL;
}

void Coin::Init() {
	scale = 1.5;
	width = size.width;
	height = size.height;
	paddingTop = 0 * scale;
	paddingBottom = 0 * scale;
	paddingLeft = 0 * scale;
	paddingRight = 0 * scale;

	exist = true;

	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/characters/coin.plist");

	idleAnimate = initAnimation("Money", 5, 0.15f);
	idleAnimate->retain();

	runAction(RepeatForever::create(idleAnimate));

	spritecache->destroyInstance();

	setScale(scale);
}