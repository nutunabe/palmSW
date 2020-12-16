#include "Leveling.h"

USING_NS_CC;

Leveling* Leveling::create()
{
	Leveling* level = new Leveling();

	level->Init();
	//level->scheduleUpdate();
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
	char str2[200] = { 0 };
	auto layer = Sprite::create("Levels/Level1/Layer1.png");
	layer->setAnchorPoint(Point(0, 0));
	layer->setPosition(Point(0, 0));
	this->addChild(layer);
	for (int i = 2; i < 10; i++) {
		sprintf(str, "Levels/Level1/Layer%d.png", i);
		sprintf(str1, "layer%d", i);
		sprintf(str2, "layer1%d", i);
		auto layer = Sprite::create(str);
		auto layer2 = Sprite::create(str);
		layer->setName(str1);
		layer2->setName(str2);
		layer->setAnchorPoint(Point(0, 0));
		layer2->setAnchorPoint(Point(0, 0));
		layer->setPosition(Point(0, 0));
		layer2->setPosition(Point(layer->getContentSize().width, 0));
		if (i > 7) {
			layer->setGlobalZOrder(1);
			layer2->setGlobalZOrder(1);
		}
		this->addChild(layer);
		this->addChild(layer2);
	}
}

void Leveling::update(float dt)
{
	char str1[200] = { 0 };
	char str12[200] = { 0 };
	for (int i = 2; i < 10; i++) {
		sprintf(str1, "layer%d", i);
		sprintf(str12, "layer1%d", i);
		auto back1 = this->getChildByName(str1);
		auto back11 = this->getChildByName(str12);
		if (back1->getPositionX() <= -back1->getContentSize().width) {
			back1->setPositionX(back11->getPositionX() + back11->getContentSize().width);
		}
		if (back11->getPositionX() <= -back11->getContentSize().width) {
			back11->setPositionX(back1->getPositionX() + back1->getContentSize().width);
		}
		if (back1->getPositionX() >= back1->getContentSize().width) {
			back1->setPositionX(back11->getPositionX() - back1->getContentSize().width);
		}
		if (back11->getPositionX() >= back11->getContentSize().width) {
			back11->setPositionX(back1->getPositionX() - back11->getContentSize().width);
		}
		//back1->setPositionX(back11->getPositionX() + back11->getContentSize().width);
	}
}

void Leveling::parallax()
{
	//if(Player::state == State::isRunning)
	char str1[200] = { 0 };
	char str11[200] = { 0 };
	if (flag != true) {
		if (direction == 1) {
			for (int i = 2; i < 10; i++) {
				sprintf(str1, "layer%d", i);
				sprintf(str11, "layer1%d", i);
				auto back1 = this->getChildByName(str1);
				auto back11 = this->getChildByName(str11);
				auto spriteAction = RepeatForever::create(MoveBy::create(7 - i / 2, Point(-this->visibleSize.width, 0)));
				auto spriteAction2 = RepeatForever::create(MoveBy::create(7 - i / 2, Point(-this->visibleSize.width, 0)));
				back1->runAction(spriteAction);
				back11->runAction(spriteAction2);
			}
			this->scheduleUpdate();
		}
		else {
			for (int i = 2; i < 10; i++) {
				sprintf(str1, "layer%d", i);
				sprintf(str11, "layer1%d", i);
				auto back1 = this->getChildByName(str1);
				auto back11 = this->getChildByName(str11);
				auto spriteAction = RepeatForever::create(MoveBy::create(7 - i / 2, Point(this->visibleSize.width, 0)));
				auto spriteAction2 = RepeatForever::create(MoveBy::create(7 - i / 2, Point(this->visibleSize.width, 0)));
				back1->runAction(spriteAction);
				back11->runAction(spriteAction2);
			}
			this->scheduleUpdate();
		}
	}
}
void Leveling::stopMoving()
{
	char str1[200] = { 0 };
	char str11[200] = { 0 };
	for (int i = 2; i < 10; i++) {
		sprintf(str1, "layer%d", i);
		sprintf(str11, "layer1%d", i);
		auto back1 = this->getChildByName(str1);
		auto back11 = this->getChildByName(str11);
		back1->stopAllActions();
		back11->stopAllActions();
	}
}
void Leveling::setDirectionRight()
{
	if (direction != 1) {
		char str1[200] = { 0 };
		char str11[200] = { 0 };
		for (int i = 2; i < 10; i++) {
			sprintf(str1, "layer%d", i);
			sprintf(str11, "layer1%d", i);
			auto back1 = this->getChildByName(str1);
			auto back11 = this->getChildByName(str11);
			if (back1->getPositionX() <= -back1->getContentSize().width) {
				back1->setPositionX(back11->getPositionX() + back11->getContentSize().width);
			}
			if (back11->getPositionX() <= -back11->getContentSize().width) {
				back11->setPositionX(back1->getPositionX() + back1->getContentSize().width);
			}
		}
		direction = 1;
	}
}
void Leveling::setDirectionLeft()
{
	if (direction != 0) {
		char str1[200] = { 0 };
		char str11[200] = { 0 };
		for (int i = 2; i < 10; i++) {
			sprintf(str1, "layer%d", i);
			sprintf(str11, "layer1%d", i);
			auto back1 = this->getChildByName(str1);
			auto back11 = this->getChildByName(str11);
			back11->setPositionX(back1->getPositionX() - back11->getContentSize().width);
		}
		direction = 0;
	}
}
