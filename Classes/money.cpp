#include "Money.h"

USING_NS_CC;

Money* Money::create(int x, int y, int width, int height) {
	Money* money = new Money();

	money->coordinate.x = x;
	money->coordinate.y = y;
	money->size.width = width;
	money->size.height = height;

	money->Init();

	return money;
}

void Money::Init() {
	auto sprite = Sprite::create("money.png");
	sprite->setAnchorPoint(Point(0, 1));
	sprite->setContentSize(size);
	sprite->setPosition(coordinate);

	this->addChild(sprite);
}