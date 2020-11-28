#include "SplashScreen.h"
#include "MainMenu.h"

USING_NS_CC;

Scene* SplashScreen::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = SplashScreen::create();

	// add layer as a child to scene
	scene->addChild(layer);

	return SplashScreen::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
	printf("Error while loading: %s\n", filename);
	printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in SplashScreen.cpp\n");
}

// on "init" you need to initialize your instance
bool SplashScreen::init()
{
	if (!Scene::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto label = Label::createWithTTF("***splash screen***", "fonts/Pixel Times.ttf", 40);
	if (label == nullptr)
	{
		problemLoading("'fonts/Pixel Times.ttf'");
	}
	else
	{
		// position the label on the center of the screen
		label->setPosition(Vec2(origin.x + visibleSize.width / 2,
			origin.y + visibleSize.height / 2 - label->getContentSize().height));

		// add the label as a child to this layer
		this->addChild(label, 1);
	}

	//auto label2 = Label::createWithTTF("***splash screen***", "fonts/Pixel Times.ttf", 30);
	//if (label2 == nullptr)
	//{
	//	problemLoading("'fonts/Pixel Times.ttf'");
	//}
	//else
	//{
	//	// position the label on the center of the screen
	//	label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
	//		origin.y + visibleSize.height - label2->getContentSize().height));

	//	// add the label as a child to this layer
	//	this->addChild(label2, 1);
	//}

	return true;
}

void SplashScreen::finishSplash(float dt) {
	// ... do whatever other initializations here
	// Show the actual main scene
	Director::getInstance()->replaceScene(MainMenu::createScene());
}

void SplashScreen::onEnter() {
	Scene::onEnter();

	// Wait for 2.0 seconds to load main scene
	this->scheduleOnce(CC_SCHEDULE_SELECTOR(SplashScreen::finishSplash), 2.0f);
}
