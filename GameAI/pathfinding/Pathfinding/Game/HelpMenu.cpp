#include "HelpMenu.h"
#include "GameApp.h"
#include "GraphicsSystem.h"

HelpMenu::~HelpMenu()
{
}

void HelpMenu::update(float timePassed)
{
	getAnimation()->update(timePassed);
	setSprite(getAnimation()->getCurrentSprite());

	getSprite()->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), H_SELECTOR_X, H_SELECTOR_Y_1, 0);
}