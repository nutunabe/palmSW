#include "Player.h"

USING_NS_CC;

Player* Player::create()
{
	Player* player = new Player();
	if (player->initWithFile("HelloSaddam.png"))
	{
		player->autorelease();
		player->initPlayer();
        player->listenKeyboard();
        player->scheduleUpdate();
		return player;
	}
	CC_SAFE_DELETE(player);
	return NULL;
}

void Player::initPlayer()
{
	direction = "right";
	is_moving = false;
}

void Player::update(float dt)
{
    if (is_moving)
    {
        if (direction == "right")
        {
            this->setPositionX(this->getPositionX() + 5);
        }
        if (direction == "left")
        {
            this->setPositionX(this->getPositionX() - 5);
        }
    }
    else
    {

    }
}

void Player::listenKeyboard()
{
	auto eventListener = EventListenerKeyboard::create();
    eventListener->onKeyPressed = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
    {
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_D:
            is_moving = true;
			direction = "right";
            break;
        case EventKeyboard::KeyCode::KEY_A:
            is_moving = true;
			direction = "left";
            break;
        }
    };
    eventListener->onKeyReleased = [this](cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
    {
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_D:
            is_moving = false;
            direction = "right";
            break;
        case EventKeyboard::KeyCode::KEY_A:
            is_moving = false;
            direction = "left";
            break;
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(eventListener, this);
}