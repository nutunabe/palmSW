#ifndef __HUD_H__
#define __HUD_H__

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "Units/Player.h"

USING_NS_CC;

class HUD : public Sprite
{
public:
    static HUD* create();
    ui::LoadingBar* healthBar;
    ui::LoadingBar* staminaBar;
    void getHit(int damage, Player* player);
    int count = 0;
    void update();
    Label* counter;
    float stamina = 100;
private:
    void Init();
    int health = 100;
};

#endif // !__HUD_H__