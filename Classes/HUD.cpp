#include "HUD.h"
#include "ui/CocosGUI.h"

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

	auto healthBar = ui::LoadingBar::create("block.png");
	healthBar->setAnchorPoint(Point(0, 1));
	healthBar->setPosition(Point(20, 750));
	healthBar->setDirection(ui::LoadingBar::Direction::LEFT);
	healthBar->setPercent(80);
	this->addChild(healthBar);
}