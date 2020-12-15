#include "Platform.h"

USING_NS_CC;

Platform* Platform::create(int x, int y, int width, int height) {
	Platform* platform = new Platform();
	if (platform->initWithFile("platform.png")) {
		platform->setPositionX(x);
		platform->setPositionY(y);
		platform->size.width = width;
		platform->size.height = height;
		platform->Init();

		platform->scale = 1.0;
		platform->width = 200;
		platform->height = 50;
		platform->paddingTop = 0 * platform->scale;
		platform->paddingBottom = 0 * platform->scale;
		platform->paddingLeft = 0 * platform->scale;
		platform->paddingRight = 0 * platform->scale;
	}
	//platform->coordinate.x = x;
	//platform->coordinate.y = y;

	return platform;
}

Platform::Platform() {
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Platform::Init() {
	//auto sprite = Sprite::create("platform.png");
	//sprite->setAnchorPoint(Point(0, 1));
	//sprite->setContentSize(size);
	//sprite->setPosition(coordinate);
	
	//this->addChild(sprite);
}

void Platform::parallax() {
	if (direction == 1) {
		auto spriteAction = RepeatForever::create(MoveBy::create(3, Point(-this->visibleSize.width, 0)));
		this->runAction(spriteAction);
		//this->scheduleUpdate();
	}
	else {
		auto spriteAction2 = RepeatForever::create(MoveBy::create(3, Point(this->visibleSize.width, 0)));
		this->runAction(spriteAction2);
		//this->scheduleUpdate();
	}
}

void Platform::setDirectionRight() {
	if (direction != 1) {
		direction = 1;
	}
}

void Platform::setDirectionLeft() {
	if (direction != 0) {
		direction = 0;
	}
}
