#include "PopupDelegates.h"

USING_NS_CC;

using namespace ui;

namespace {
    cocos2d::Size CONFIRM_DIALOGUE_SIZE_OFFSET = Size(250, 150);
    const float ANIMATION_TIME = 0.15f;
    const float FADE_RATIO = 150;
}

namespace FONT {
    const float LABEL_OFFSET = 30;
    const float DESCRIPTION_TEXT_SIZE = 45;
    const float TITLE_TEXT_SIZE = 70;
    const char* GAME_FONT = "fonts/Pixel Times.ttf";
    const float LABEL_STROKE = 4;
}

namespace IMAGEPATH {
    const char* OK_BUTTON = "res/Popup/okpix1.png";
    const char* OK_BUTTON_PRESSED = "res/Popup/okpix1-2.png";
    const char* CANCEL_BUTTON = "res/Popup/cancelpix1-2.png";
    const char* CANCEL_BUTTON_PRESSED = "res/Popup/cancelpix1.png";
    const char* BACKGROUND_IMAGE = "res/Popup/popupbasepix.png";
}
namespace UICustom {

    PopupDelegates* PopupDelegates::create()
    {
        PopupDelegates* node = new (std::nothrow)PopupDelegates();
        if (node && node->init())
        {
            node->autorelease();
            return node;
        }
        CC_SAFE_DELETE(node);
        return nullptr;
    }

    bool PopupDelegates::init()
    {
        Size winSize = Director::getInstance()->getWinSize();

        if (!LayerRadialGradient::initWithColor(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, FADE_RATIO), winSize.width / 1.7f, winSize / 2, 0.075f))
        {
            return false;
        }
        this->setOpacity(0);
        show(true);
        this->setUpTouches();


        return true;
    }

    void PopupDelegates::show(const bool animated)
    {
        if (animated) {
            this->runAction(FadeTo::create(ANIMATION_TIME, FADE_RATIO));
        }
        else {
            this->setOpacity(FADE_RATIO);
        }
    }
    void PopupDelegates::dismiss(const bool animated)
    {
        if (animated) {
            this->runAction(Sequence::create(FadeTo::create(ANIMATION_TIME, 0), RemoveSelf::create(), NULL));
        }
        else {
            this->removeFromParentAndCleanup(true);
        }
    }

    void PopupDelegates::setUpTouches()
    {

        auto listener = EventListenerTouchOneByOne::create();
        listener->setSwallowTouches(true);
        listener->onTouchBegan = [=](Touch* touch, Event* event) {
            if (_bg) {
                if (!_bg->getBoundingBox().containsPoint(this->convertToNodeSpace(touch->getLocation())))
                {
                    this->dismiss(true);
                }
            }
            else {
                this->dismiss(true);
            }
            return true;
        };
        _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    }

    Popup* Popup::createAsMessage(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, const std::string& msg3, Player* player, HUD* hud)
    {
        return createAsConfirmDialogue(title, msg, msg1, msg2, msg3,NULL, player, hud);
    }

    Popup* Popup::createAsConfirmDialogue(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, const std::string& msg3, const std::function<void()>& YesFunc, Player* player, HUD* hud)
    {
        return create(title, msg, msg1, msg2, msg3, NULL, YesFunc, player, hud);
    }

    Popup* Popup::create(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, const std::string& msg3, cocos2d::Label* lbl, const std::function<void()>& YesFunc, Player* player, HUD* hud)
    {
        Popup* node = new (std::nothrow)Popup();
        Size visibleSize = Director::getInstance()->getVisibleSize();
        if (node && node->init())
        {
            auto lbl = Label::createWithTTF(msg, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            lbl->setColor(Color3B::BLUE);
            auto lbl1 = Label::createWithTTF(msg1, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            lbl1->setColor(Color3B::BLUE);
            auto lbl2 = Label::createWithTTF(msg2, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            lbl2->setColor(Color3B::BLUE);
            auto lbl3 = Label::createWithTTF(msg3, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            lbl3->setColor(Color3B::BLUE);

            auto Button_1 = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref* sender) {
                if (hud->count >= 1 && player->getHealth() < player->maxHealth) {
                    int k = rand() % player->maxHealth;
                    if (player->getHealth() + k > player->maxHealth) {
                        player->setHealth(player->maxHealth - player->getHealth());
                    }
                    else {
                        player->setHealth(k);
                    }
                    hud->healthBar->setPercent(player->getHealth());
                    hud->count -= 1;
                    hud->update();
                }
            });

            auto Button_2 = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref* sender) {
                if (hud->count >= 2 && player->getHealth() < player->maxHealth) {
                    player->setHealth(player->maxHealth - player->getHealth());
                    hud->healthBar->setPercent(player->getHealth());
                    hud->count -= 2;
                    hud->update();
                }
            });

            auto Button_3 = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref* sender) {
                if (hud->count >= 1) {
                    player->upgradeDamage(10.0);
                    hud->count -= 1;
                    hud->update();
                }
            });

            auto Button_close = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [=](Ref* sender) {
                node->dismiss(true);
            });

            Menu* menu = Menu::create(Button_1, Button_2, Button_3, Button_close, NULL);
            node->addChild(menu, 2);
            menu->setPosition(Point(3790, 275));
            menu->alignItemsVerticallyWithPadding(FONT::LABEL_OFFSET / 2);

            lbl->setPosition(Point(3500, 390));
            lbl1->setPosition(Point(3500, 315));
            lbl2->setPosition(Point(3500, 235));
            lbl3->setPosition(Point(3500, 160));

            CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);

            node->addChild(lbl3, 2);
            node->initBg(lbl3->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->addChild(lbl, 2);
            node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->addChild(lbl2, 2);
            node->initBg(lbl2->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->addChild(lbl1, 2);
            node->initBg(lbl1->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);

            node->autorelease();
            return node;
        }
        CC_SAFE_DELETE(node);
        return nullptr;
    }



    void Popup::initBg(Size size, const std::string& title)
    {
        Size winSize = Director::getInstance()->getWinSize();

        _bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE);
        _bg->setPosition(Point(3500, 280));
        _bg->setScale9Enabled(true);
        _bg->setContentSize(size);
        this->addChild(_bg);

        Label* heading = Label::createWithTTF(title, FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
        heading->setPosition(Point(3500, 305));
        this->addChild(heading);
    }
}