#ifndef __HUD_H__
#define __HUD_H__

#include<cocos2d.h>

USING_NS_CC;

class HUD : public ProgressTimer
{
public:
    static HUD* create();
private:
    ProgressTimer healthBar;
    void Init();
};

#endif // !__HUD_H__