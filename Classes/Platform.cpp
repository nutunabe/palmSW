#include "Platform.h"

USING_NS_CC;

Platform* Platform::create(int x, int y, int width, int height) {
	Platform* platform = new Platform();

	platform->coordinate.x = x;
	platform->coordinate.y = y;
	platform->size.width = width;
	platform->size.height = height;

	platform->Init();

	return platform;
}

Platform::Platform() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Platform::Init() {
	auto sprite = Sprite::create("platform.png");
	sprite->setAnchorPoint(Point(0, 1));
	sprite->setContentSize(size);
	sprite->setPosition(coordinate);

	this->addChild(sprite);
}