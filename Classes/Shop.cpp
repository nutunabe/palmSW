#include "Shop.h"

USING_NS_CC;

Shop* Shop::create(int x, int y, int width, int height) {
	Shop* shop = new Shop();

	if (shop->initWithFile("shop.png")) {
		shop->setPositionX(x);
		shop->setPositionY(y);
		shop->size.width = width;
		shop->size.height = height;

		shop->scale = 0.5;
		shop->width = shop->size.width;
		shop->height = shop->size.height;
		shop->paddingTop = 0 * shop->scale;
		shop->paddingBottom = 0 * shop->scale;
		shop->paddingLeft = 0 * shop->scale;
		shop->paddingRight = 0 * shop->scale;

		shop->setScale(shop->scale);
	}
	return shop;
}
