#ifndef __HUD_H__
#define __HUD_H__

#include<cocos2d.h>
#include "ui/CocosGUI.h"
#include "Player.h"

USING_NS_CC;

class HUD : public Sprite
{
public:
    static HUD* create();
    ui::LoadingBar* healthBar;
    void getHit(int damage, Player* player);
private:
    void Init();
    int health = 100;
};

#endif // !__HUD_H__