#include "Leveling.h"

USING_NS_CC;

Leveling* Leveling::create()
{
	Leveling* level = new Leveling();

	level->Init();
	level->scheduleUpdate();
	/*auto backgroundLayer1 = Sprite::create("Levels/Layer_0010_1.png");
	backgroundLayer1->setScale(level->visibleSize.width, level->visibleSize.height);
	backgroundLayer1->setAnchorPoint(Point(0, 0));
	backgroundLayer1->setPosition(Point(0, 0));
	level->addChild(backgroundLayer1);

	auto backgroundLayer2 = Sprite::create("Levels/Layer_0008_3.png");
	backgroundLayer2->setScale(level->visibleSize.width, level->visibleSize.height);
	backgroundLayer2->setAnchorPoint(Point(0, 0));
	backgroundLayer2->setPosition(Point(0, 150));
	level->addChild(backgroundLayer2);

	auto backgroundLayer10 = Sprite::create("Levels/Layer_0001_8.png");
	backgroundLayer10->setAnchorPoint(Point(0, 0));
	backgroundLayer10->setPosition(Point(0, 0));
	level->addChild(backgroundLayer10);*/
	//auto spriteAction = RepeatForever::create(MoveBy::create(2.0, Point(level->visibleSize.width, 0)));
	//backgroundLayer1->runAction(spriteAction);


	return level;
}

Leveling::Leveling()
{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();
}

void Leveling::Init() 
{
	char str[200] = { 0 };
	char str1[200] = { 0 };
	for (int i = 1; i < 10; i++) {
		sprintf(str, "Levels/Level1/Layer%d.png", i);
		sprintf(str1, "layer%d", i);
		auto layer = Sprite::create(str);
		layer->setName(str1);
		layer->setAnchorPoint(Point(0, 0));
		layer->setPosition(Point(0, 0));
		//auto spriteAction = RepeatForever::create(MoveBy::create(11 - i, Point(-this->visibleSize.width, 0)));
		//layer->runAction(spriteAction);
		this->addChild(layer);
		background.pushBack(layer);
	}
}

void Leveling::update(float dt)
{
	char str[200] = { 0 };
	for (int i = 1; i < 10; i++)
	{
		sprintf(str, "layer%d", i);
		auto back = this->getChildByName(str);
		if (back->getPositionX() <= -this->visibleSize.width) {
			back->setPositionX(0);
		}
	}
}

void Leveling::checkMoving() 
{
	//if()
}
