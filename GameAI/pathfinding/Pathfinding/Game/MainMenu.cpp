#include "MainMenu.h"
#include "GameApp.h"
#include "GraphicsSystem.h"

//Update function for the main menu
void MainMenu::update(float timePassed)
{
	mpAnimation->update(timePassed);
	mpSprite = mpAnimation->getCurrentSprite();

	switch (mSelection)
	{
	case MainSelectionState::PLAY:
		mpSprite->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), SELECTOR_X, SELECTOR_Y_1, 0);
		break;
	case MainSelectionState::HELP:
		mpSprite->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), SELECTOR_X, SELECTOR_Y_2, 0);
		break;
	case MainSelectionState::CREDITS:
		mpSprite->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), SELECTOR_X, SELECTOR_Y_3, 0);
		break;
	case MainSelectionState::QUIT:
		mpSprite->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), SELECTOR_X, SELECTOR_Y_4, 0);
		break;
	}

}