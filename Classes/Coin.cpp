#include "Coin.h"

USING_NS_CC;

Coin* Coin::create(int x, int y, int width, int height) {
	Coin* coin = new Coin();

	coin->coordinate.x = x;
	coin->coordinate.y = y;
	coin->size.width = width;
	coin->size.height = height;

	coin->Init();

	return coin;
}

void Coin::Init() {
	scale = 1.0;

	width = 40;
	height = 20;

	paddingTop = 0 * scale;
	paddingBottom = 0 * scale;
	paddingLeft = 0 * scale;
	paddingRight = 0 * scale;

	auto sprite = Sprite::create("money.png");
	sprite->setAnchorPoint(Point(0.5, 0.5));
	sprite->setContentSize(size);
	sprite->setPosition(coordinate);
	exist = true;
	this->addChild(sprite);
}