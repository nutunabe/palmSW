#include "Leveling.h"

USING_NS_CC;

Leveling* Leveling::create()
{
	Leveling* level = new Leveling();

	auto backgroundLayer1 = Sprite::create("Levels/Layer_0010_1.png");
	backgroundLayer1->setScale(level->visibleSize.width, level->visibleSize.height);
	backgroundLayer1->setAnchorPoint(Point(0, 0));
	backgroundLayer1->setPosition(Point(0,0));
	level->addChild(backgroundLayer1);

	auto backgroundLayer2 = Sprite::create("Levels/Layer_0008_3.png");
	backgroundLayer2->setScale(level->visibleSize.width, level->visibleSize.height);
	backgroundLayer2->setAnchorPoint(Point(0, 0));
	backgroundLayer2->setPosition(Point(0, 150));
	level->addChild(backgroundLayer2);

	auto backgroundLayer10 = Sprite::create("Levels/Layer_0001_8.png");
	backgroundLayer10->setAnchorPoint(Point(0, 0));
	backgroundLayer10->setPosition(Point(0,0));
	level->addChild(backgroundLayer10);
	//auto spriteAction = RepeatForever::create(MoveBy::create(2.0, Point(level->visibleSize.width, 0)));
	//backgroundLayer1->runAction(spriteAction);


	return level;
}

Leveling::Leveling() 
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Leveling::Scrolling(Layer* layer)
{
	auto backgroundLayer1 = Sprite::create("Layer_0009_2.png");
	backgroundLayer1->setPosition(Point(0, 0));
}