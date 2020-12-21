#include "HUD.h"

USING_NS_CC;

HUD* HUD::create(Player* player) {
	HUD* hud = new HUD();

	hud->Init(player);

	return hud;
}

void HUD::Init(Player* player) {
	this->player = player;

	auto hBBackground = Sprite::create("res/hud/hb_bg.png");
	hBBackground->setAnchorPoint(Point(0, 1));
	hBBackground->setPosition(Point(20, 750));
	this->addChild(hBBackground);

	healthBar = ui::LoadingBar::create("res/hud/hb_h.png");
	healthBar->setAnchorPoint(Point(0, 1));
	healthBar->setPosition(Point(76, 742));
	healthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	healthBar->setPercent(player->getHealth());
	this->addChild(healthBar);

	auto hBBackground1 = Sprite::create("res/hud/hb_h_bg.png");
	hBBackground1->setAnchorPoint(Point(0, 1));
	hBBackground1->setPosition(Point(76, 742));
	this->addChild(hBBackground1);

	staminaBar = ui::LoadingBar::create("res/hud/hb_s.png");
	staminaBar->setAnchorPoint(Point(0, 1));
	staminaBar->setPosition(Point(72, 706));
	staminaBar->setDirection(ui::LoadingBar::Direction::LEFT);
	staminaBar->setPercent(player->getStamina());
	this->addChild(staminaBar);

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	char str[200] = { 0 };
	sprintf(str, "Coin: %d", count);
	counter = Label::createWithTTF(str, "fonts/Pixel Times.ttf", 27);
	if (counter == nullptr)
	{
		printf("Не повезло");
	}
	else
	{
		// position the label on the center of the screen
		counter->setAnchorPoint(Point(0, 1));
		counter->setPosition(Point(20, 650));

		// add the label as a child to this layer
		this->addChild(counter, 5);
	}
}

void HUD::getHit(int damage) {
	if (player->getHealth() <= 0) {
		player->stillState = State::isDying;
		player->state = player->stillState;
	}
	else {
		healthBar->setPercent(player->getHealth());
	}
}

void HUD::update() {
	staminaBar->setPercent(player->getStamina());
	removeChild(counter, true);
	char str[200] = { 0 };
	sprintf(str, "Coin: %d", count);
	counter = Label::createWithTTF(str, "fonts/Pixel Times.ttf", 27);
	if (counter == nullptr)
	{
		printf("Не повезло");
	}
	else
	{
		// position the label on the center of the screen
		counter->setAnchorPoint(Point(0, 1));
		counter->setPosition(Point(20, 650));

		// add the label as a child to this layer
		this->addChild(counter, 5);
	}
}