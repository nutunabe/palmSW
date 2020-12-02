#include "HUD.h"

USING_NS_CC;

HUD* HUD::create() {
	HUD* hud = new HUD();

	hud->Init();

	return hud;
}

void HUD::Init() {
	auto hBBackground = Sprite::create("block2.png");
	hBBackground->setAnchorPoint(Point(0, 1));
	hBBackground->setPosition(Point(20, 750));
	this->addChild(hBBackground);

	healthBar = ui::LoadingBar::create("block.png");
	healthBar->setAnchorPoint(Point(0, 1));
	healthBar->setPosition(Point(20, 750));
	healthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	healthBar->setPercent(health);
	this->addChild(healthBar);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	char str[200] = { 0 };
	sprintf(str, "Coin: %d", count);
	counter = Label::createWithTTF(str, "fonts/Pixel Times.ttf", 27);
	if (counter == nullptr)
	{
		printf("�� �������");
	}
	else
	{
		// position the label on the center of the screen
		counter->setAnchorPoint(Point(0, 1));
		counter->setPosition(Point(20, 700));

		// add the label as a child to this layer
		this->addChild(counter, 5);
	}
}

void HUD::getHit(int damage, Player* player) {
	if (health <= 0) {
		player->stillState = State::isDying;
		player->state = player->stillState;
	}
	else {
		health -= damage;
		healthBar->setPercent(health);
	}
}

void HUD::update() {
	removeChild(counter, true);
	char str[200] = { 0 };
	sprintf(str, "Coin: %d", count);
	counter = Label::createWithTTF(str, "fonts/Pixel Times.ttf", 27);
	if (counter == nullptr)
	{
		printf("�� �������");
	}
	else
	{
		// position the label on the center of the screen
		counter->setAnchorPoint(Point(0, 1));
		counter->setPosition(Point(20, 700));

		// add the label as a child to this layer
		this->addChild(counter, 5);
	}
}