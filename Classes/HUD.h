#ifndef __HUD_H__
#define __HUD_H__

#include <cocos2d.h>
#include "ui/CocosGUI.h"
#include "Units/Player.h"

USING_NS_CC;

class HUD : public Sprite
{
public:
    static HUD* create(Player* player);
    ui::LoadingBar* healthBar;
    ui::LoadingBar* staminaBar;
    void getHit(int damage);
    int count = 0;
    void update();
    Label* counter;
private:
    void Init(Player* player);
    Player* player;

    int maxHealth;
    int maxStamina;
};

#endif // !__HUD_H__