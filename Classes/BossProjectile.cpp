#include "BossProjectile.h"

BossProjectile* BossProjectile::create()
{
	BossProjectile* bossproj = new BossProjectile();
	if (bossproj->init())
	{
		srand(time(nullptr));
		bossproj->setAnchorPoint(Point(0.5f, 0.5f));
		bossproj->autorelease();
		bossproj->scheduleUpdate();
		bossproj->initBossProjectile();
		return bossproj;
	}
	CC_SAFE_DELETE(bossproj);
	return NULL;
}

void BossProjectile::initBossProjectile()
{
	velocityY = 0;
	scale = 5;
	width = 45 * scale;
	height = 45 * scale;
	paddingTop = -13 * scale;
	paddingBottom = -4 * scale;
	paddingLeft = 6 * scale;
	paddingRight = -6 * scale;

	spritecache = SpriteFrameCache::getInstance();
	spritecache->addSpriteFramesWithFile("res/characters/mushroom.plist");

	breakAnimate = initAnimation("Projectile_sprite", 8, 0.05f);
	breakAnimate->retain();

	fallAnimate = initAnimation("Projectile_sprite", 1, 0.2f);
	fallAnimate->retain();

	setScale(scale);
	spritecache->destroyInstance();
}

Animate* BossProjectile::initAnimation(char* name, int size, float dt) {
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int _i = 0; _i < size; _i++) {
		memset(str, 0, sizeof str);
		sprintf(str, "%s-%d.png", name, _i);
		frames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	auto animation = Animation::createWithSpriteFrames(frames, dt);
	return Animate::create(animation);
}

int BossProjectile::getWidth() {
	return width;
}

int BossProjectile::getHeight() {
	return height;
}

float BossProjectile::getTop() {
	return getPositionY() + height / 2 + paddingTop;
}

float BossProjectile::getBottom() {
	return getPositionY() - height / 2 + paddingBottom;
}

float BossProjectile::getLeft() {
	return getPositionX() - width / 2 + paddingLeft;
}

float BossProjectile::getRight() {
	return getPositionX() + width / 2 + paddingRight;
}

void BossProjectile::update(float dt) {
	if (getPosition() != Point(0, 800)) {
		if (getPositionY() > 75) {
			velocityY -= 9.81 * 0.1;
			setPositionY(getPositionY() + velocityY);
			runAction(RepeatForever::create(fallAnimate));
		}
		else {
			velocityY = 0;
			runAction(Repeat::create(breakAnimate, 1));

			if (breakAnimate->getCurrentFrameIndex() == 7) {
				stopAllActions();
				breakAnimate->update(0);
				setPosition(Point(0, 800));
			}
		}
	}
}
