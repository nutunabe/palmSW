#include "Units/SpriteUnit.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

class Shop : public SpriteUnit 
{
public:
	static Shop* create(int x, int y, int width, int height);
	Size size;
private:
	Size visibleSize;
	Vec2 origin;
};

