#include "PopupDelegates.h"

USING_NS_CC;

using namespace ui;

namespace {
    cocos2d::Size CONFIRM_DIALOGUE_SIZE_OFFSET = Size(175, 150);
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
    const char* OK_BUTTON = "res/Popup/Ok.png";
    const char* OK_BUTTON_PRESSED = "res/Popup/OkPressed.png";
    const char* CANCEL_BUTTON = "res/Popup/Cancel.png";
    const char* CANCEL_BUTTON_PRESSED = "res/Popup/CancelPressed.png";
    const char* CLOSE_BUTTON = "res/Popup/close.png";
    const char* BACKGROUND_IMAGE = "res/Popup/popUpBase.png";
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

    Popup* Popup::createAsMessage(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, Player* player, HUD* hud)
    {
        return createAsConfirmDialogue(title, msg, msg1, msg2, NULL, player, hud);
    }

    Popup* Popup::createAsConfirmDialogue(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, const std::function<void()>& YesFunc, Player* player, HUD* hud)
    {
        return create(title, msg, msg1, msg2, NULL, YesFunc, player, hud);
    }

    Popup* Popup::create(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, cocos2d::Label* lbl, const std::function<void()>& YesFunc, Player* player, HUD* hud)
    {
        Popup* node = new (std::nothrow)Popup();
        Size visibleSize = Director::getInstance()->getVisibleSize();
        if (node && node->init())
        {
            auto lbl = Label::createWithTTF(msg, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            lbl->setPosition(Point(3500, 350));
            lbl->enableShadow(Color4B::BLACK, Size(0, -2));
            //lbl->setVerticalAlignment(TextVAlignment::CENTER);
            auto lbl1 = Label::createWithTTF(msg1, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            lbl1->setPosition(Point(3500, 285));
            lbl1->enableShadow(Color4B::BLACK, Size(0, -2));
            //lbl->setVerticalAlignment(TextVAlignment::CENTER);
            auto lbl2 = Label::createWithTTF(msg2, FONT::GAME_FONT, FONT::DESCRIPTION_TEXT_SIZE);
            lbl2->setPosition(Point(3500, 205));
            lbl2->enableShadow(Color4B::BLACK, Size(0, -2));
            //lbl->setVerticalAlignment(TextVAlignment::CENTER);

            auto Button_1 = MenuItemImage::create(IMAGEPATH::OK_BUTTON, IMAGEPATH::OK_BUTTON_PRESSED, [=](Ref* sender) {
                CCLOG("button 1 pre");
                if (hud->count >= 1 && player->getHealth() < player->maxHealth) {
                    CCLOG("button 1 act");
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
                CCLOG("button 2 pre");
                if (hud->count >= 2 && player->getHealth() < player->maxHealth) {
                    CCLOG("button 2 act");
                    player->setHealth(player->maxHealth - player->getHealth());
                    hud->healthBar->setPercent(player->getHealth());
                    hud->count -= 2;
                    hud->update();
                }
            });

            auto Button_close = MenuItemImage::create(IMAGEPATH::CANCEL_BUTTON, IMAGEPATH::CANCEL_BUTTON_PRESSED, [=](Ref* sender) {
                node->dismiss(true);
            });

            Menu* menu = Menu::create(Button_1, Button_2, Button_close, NULL);
            node->addChild(menu, 2);
            menu->setPosition(Point(3770, 275));
            menu->alignItemsVerticallyWithPadding(FONT::LABEL_OFFSET / 2);

            lbl->setPosition(Point(3500, 350));
            CONFIRM_DIALOGUE_SIZE_OFFSET = Size(CONFIRM_DIALOGUE_SIZE_OFFSET.width, 300);
            node->addChild(lbl, 3);
            node->initBg(lbl->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->addChild(lbl1, 3);
            node->initBg(lbl1->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->addChild(lbl2, 3);
            node->initBg(lbl2->getContentSize() + CONFIRM_DIALOGUE_SIZE_OFFSET, title);
            node->autorelease();
            return node;
        }

        CC_SAFE_DELETE(node);
        return nullptr;
    }



    void Popup::initBg(Size size, const std::string& title)
    {

        Size winSize = Director::getInstance()->getVisibleSize();

        _bg = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE);
        this->addChild(_bg);

        _bg->setPosition(Point(3500, 280));
        _bg->setScale9Enabled(true);
        _bg->setContentSize(size);

        /*ui::ImageView* fill = ui::ImageView::create(IMAGEPATH::BACKGROUND_IMAGE);
        _bg->addChild(fill);
        fill->setColor(Color3B(210, 210, 210));
        fill->setScale9Enabled(true);
        fill->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
        fill->setPosition(Point(3000, 375));*
        fill->setContentSize(Size(size.width - FONT::LABEL_OFFSET / 2, size.height - FONT::LABEL_OFFSET * 2));*/

        Label* heading = Label::createWithTTF(title, FONT::GAME_FONT, FONT::TITLE_TEXT_SIZE);
        heading->setPosition(Point(3500, 305));
        _bg->addChild(heading);
        heading->enableOutline(Color4B::BLACK, FONT::LABEL_STROKE);
        heading->enableShadow(Color4B::BLACK, Size(0, -3));
    }
}