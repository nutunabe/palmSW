#include "SpriteUnit.h"

void SpriteUnit::update() {
	// . . .
}

Animate* SpriteUnit::initAnimation(char* name, int size, float dt) {
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

Animate* SpriteUnit::initAnimation(char* name, int size, float dt, char* gg) {
	Vector<SpriteFrame*> frames;
	char str[200] = { 0 };
	for (int _i = 0; _i < size; _i++) {
		memset(str, 0, sizeof str);
		sprintf(str, "%s-%d.png", name, _i);
		frames.pushBack(spritecache->getSpriteFrameByName(str));
	}
	frames.pushBack(spritecache->getSpriteFrameByName(str));
	auto animation = Animation::createWithSpriteFrames(frames, dt);
	return Animate::create(animation);
}

int SpriteUnit::getWidth() {
	return width;
}

int SpriteUnit::getHeight() {
	return height;
}

float SpriteUnit::getTop() {
	return getPositionY() + height / 2 + paddingTop;
}

float SpriteUnit::getBottom() {
	return getPositionY() - height / 2 + paddingBottom;
}

float SpriteUnit::getLeft() {
	return getPositionX() - width / 2 + paddingLeft;
}

float SpriteUnit::getRight() {
	return getPositionX() + width / 2 + paddingRight;
}
