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