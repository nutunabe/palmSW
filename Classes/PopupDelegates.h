#ifndef Popup_Delegates_h
#define Popup_Delegates_h

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Units/Player.h"
#include "HUD.h"

namespace UICustom {


    class PopupDelegates : public cocos2d::LayerRadialGradient
    {

    public:
        bool isshow;
        static PopupDelegates* create();

    protected:
        virtual bool init();
        virtual void setUpTouches();


        virtual void show(const bool animated = true);
        virtual void dismiss(const bool animated = true);
        void setAnimated(const bool animated) { _isAnimated = animated; };

        cocos2d::ui::ImageView* _bg = nullptr;
    private:
        bool _isAnimated = false;
        void update();
    };



    class Popup : public PopupDelegates
    {

    public:
        static Popup* createAsMessage(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, const std::string& msg3, Player* player, HUD* hud);
        static Popup* createAsConfirmDialogue(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, const std::string& msg3, const std::function<void()>& YesFunc, Player* player, HUD* hud);
        static Popup* create(const std::string& title, const std::string& msg, const std::string& msg1, const std::string& msg2, const std::string& msg3, cocos2d::Label* lbl, const std::function<void()>& YesFunc, Player* player, HUD* hud);


    private:
        void initBg(const cocos2d::Size size, const std::string& title);
    };

}

#endif