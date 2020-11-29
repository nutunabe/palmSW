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
	/*auto rectNode = DrawNode::create();
	auto physicsBody = PhysicsBody::createPolygon(rectangle, 1, PhysicsMaterial(0.1f, 1.0f, 0.0f));
	Color4F green(255, 255, 255, 1);
	rectNode->addComponent(physicsBody);
	rectNode->drawPolygon(rectangle, 4, green, 1, green);
	auto sprite = Sprite::create("block.png");
	sprite->setAnchorPoint(Point(0, 0));
	sprite->setContentSize(Size(100, 50));
	sprite->setPosition(Vec2(300, 150));
	sprite->addComponent(physicsBody);
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

	this->addChild(sprite);*/
}