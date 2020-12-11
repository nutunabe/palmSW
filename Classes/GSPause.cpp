#include "GSPause.h"

USING_NS_CC;

Layer* GSPause::addLayer()
{
    auto pause = GSPause::create();

    auto layer = Layer::create();
    
    layer->setColor(Color3B::BLUE);

    pause->addChild(layer);

    return pause;
}

/*bool GSPause::init() {

    this->addLayer()

    return true;
}*/
