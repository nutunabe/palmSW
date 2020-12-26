#include "MainMenu.h"


USING_NS_CC;

Scene* MainMenu::createScene() {
	auto scene = Scene::create();

	auto layer = MainMenu::create();


    layer->setGlobalZOrder(4);

	scene->addChild(layer);

	return scene;
}

static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in GameScene.cpp\n");
}

bool MainMenu::init() {
    musicVolume = js.getVolume("musicVolume");
    soundfxVolume = js.getVolume("soundfxVolume");
    musicID = AudioEngine::play2d(BG_SOUND, true, musicVolume);

	if ( !Layer::init()) {
		return false;
	}

    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();

    
    auto backgroundSprite = Sprite::create(BG_IMAGE);
    backgroundSprite->setContentSize(visibleSize);
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    this->addChild(backgroundSprite);

    showMainMenu();

    return true;
}

void MainMenu::GoToGameScene(Ref* sender)
{
    Director::getInstance()->replaceScene(GameScene::createScene());

    AudioEngine::stopAll();
    /*auto scene = GameScene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(TRANSITION_TIME, scene));*/
}

void MainMenu::menuCloseCallback(Ref* sender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);

}
void MainMenu::showSettings( Ref* sender ) {
    this->removeChildByName("menu", true);

    auto musicLabel = Label::createWithTTF("Music:", FONT_DEFINITION, 24);
    musicLabel->setName("music");
    musicLabel->setPosition(Point(visibleSize.width / 2 + origin.x - musicLabel->getContentSize().width, visibleSize.height / 2 + origin.y + musicLabel->getContentSize().height * 3));
    this->addChild(musicLabel, 2);

    auto soundfxLabel = Label::createWithTTF("Sound FX:", FONT_DEFINITION, 24);
    soundfxLabel->setName("soundFX");
    soundfxLabel->setPosition(Point(visibleSize.width / 2 + origin.x - soundfxLabel->getContentSize().width / 1.3, visibleSize.height / 2 + origin.y + soundfxLabel->getContentSize().height * 1.5));
    this->addChild(soundfxLabel, 2);

    //auto settingsItem = MenuItemImage::create("settings.png", "settings.png", CC_CALLBACK_1(MainMenu::showSettings, this));
    auto backLabel = Label::createWithTTF("Back", FONT_DEFINITION, 24);
    auto backItem = MenuItemLabel::create(backLabel, CC_CALLBACK_1(MainMenu::showMenu, this));
    backItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto menu = Menu::create(backItem, NULL);
    menu->setName("menu");
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);

    slider = ui::Slider::create();
    slider->setTouchEnabled(true);
    slider->setName("musicVolume");
    slider->loadBarTexture("Slider_Back.png"); // как будет выглядеть Slider
    slider->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    slider->loadProgressBarTexture("Slider_PressBar.png");

    slider->setPercent(musicVolume * 100);

    slider->setPosition(Point(visibleSize.width / 2 + origin.x + musicLabel->getContentSize().width, visibleSize.height / 2 + origin.y + musicLabel->getContentSize().height * 3));

    slider->addEventListener(CC_CALLBACK_2(MainMenu::sliderEvent, this));
    this->addChild(slider, 4);

    sliderFX = ui::Slider::create();
    sliderFX->setTouchEnabled(true);
    sliderFX->setName("soundfxVolume");
    sliderFX->loadBarTexture("Slider_Back.png"); // как будет выглядеть Slider
    sliderFX->loadSlidBallTextures("SliderNode_Normal.png", "SliderNode_Press.png", "SliderNode_Disable.png");
    sliderFX->loadProgressBarTexture("Slider_PressBar.png");

    sliderFX->setPercent(soundfxVolume * 100);

    sliderFX->setPosition(Point(visibleSize.width / 2 + origin.x + musicLabel->getContentSize().width, visibleSize.height / 2 + origin.y + soundfxLabel->getContentSize().height * 1.5));

    sliderFX->addEventListener(CC_CALLBACK_2(MainMenu::sliderEvent, this));
    this->addChild(sliderFX, 4);

    auto label2 = Label::createWithTTF(u8" \"A\", \"D\"; F-Attack, SPACE-Jump, 1-Take Hit, 2-Die", FONT_DEFINITION, 27);
    if (label2 == nullptr)
    {
        problemLoading("'fonts/Pixel Times.ttf'");
    }
    else
    {
        // position the label on the center of the screen
        label2->setPosition(Vec2(origin.x + visibleSize.width / 2,
            origin.y + label2->getContentSize().height/* + visibleSize.height - label2->getContentSize().height*/));

        label2->setName("keyboard");
        // add the label as a child to this layer
        this->addChild(label2, 0);
    }
}

void MainMenu::showMenu(Ref* sender) {
    this->removeChildByName("menu", true);
    this->removeChildByName("musicVolume", true);
    this->removeChildByName("soundFX", true);
    this->removeChildByName("soundfxVolume", true);
    this->removeChildByName("music", true);
    this->removeChildByName("keyboard", true);

    CCLOG("%d", slider->getPercent());
    //AudioEngine::setVolume(musicID, float(musicVolume));

    //auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(MainMenu::GoToGameScene, this));
    auto playLabel = Label::createWithTTF("Play", FONT_DEFINITION, 24);
    auto playItem = MenuItemLabel::create(playLabel, CC_CALLBACK_1(MainMenu::GoToGameScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + playItem->getContentSize().height * 2));

    //auto settingsItem = MenuItemImage::create("settings.png", "settings.png", CC_CALLBACK_1(MainMenu::showSettings, this));
    auto settingsLabel = Label::createWithTTF("Settings", FONT_DEFINITION, 24);
    auto settingsItem = MenuItemLabel::create(settingsLabel, CC_CALLBACK_1(MainMenu::showSettings, this));
    settingsItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto menu = Menu::create(playItem, settingsItem, NULL);
    menu->setName("menu");
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this)
    );

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);

}

void MainMenu::showMainMenu() {
    //auto playItem = MenuItemImage::create("Play Button.png", "Play Button Clicked.png", CC_CALLBACK_1(MainMenu::GoToGameScene, this));
    auto playLabel = Label::createWithTTF("Play", FONT_DEFINITION, 24);
    auto playItem = MenuItemLabel::create(playLabel, CC_CALLBACK_1(MainMenu::GoToGameScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + playItem->getContentSize().height * 2));

    //auto settingsItem = MenuItemImage::create("settings.png", "settings.png", CC_CALLBACK_1(MainMenu::showSettings, this));
    auto settingsLabel = Label::createWithTTF("Settings", FONT_DEFINITION, 24);
    auto settingsItem = MenuItemLabel::create(settingsLabel, CC_CALLBACK_1(MainMenu::showSettings, this));
    settingsItem->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));

    auto menu = Menu::create(playItem, settingsItem, NULL);
    menu->setName("menu");
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 2);

    auto closeItem = MenuItemImage::create(
        "CloseNormal.png",
        "CloseSelected.png",
        CC_CALLBACK_1(MainMenu::menuCloseCallback, this)
    );

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width / 2;
        float y = origin.y + closeItem->getContentSize().height / 2;
        closeItem->setPosition(Vec2(x, y));
    }

    menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 2);
}


void MainMenu::sliderEvent(Ref* sender, ui::Slider::EventType type)
{
    if (type == ui::Slider::EventType::ON_PERCENTAGE_CHANGED)
    {
        auto slider = dynamic_cast<ui::Slider*>(sender);
        int temp = slider->getPercent();
        float dt = temp;
        if (slider->getName() == "musicVolume") {
            musicVolume = dt / 100;
            AudioEngine::setVolume(musicID, musicVolume);

            js.setVolume("musicVolume", musicVolume);

        }
        else if (slider->getName() == "soundfxVolume"){
            soundfxVolume = dt / 100;
            AudioEngine::setVolume(soundfxID, js.getVolume("soundfxVolume"));
            soundfxID = AudioEngine::play2d(PLAYER_ATTACK, false, soundfxVolume);
            
            js.setVolume("soundfxVolume", soundfxVolume);
            
        }
    }
}
