#include "MainMenu.h"
#include "GameApp.h"
#include "GraphicsSystem.h"

MainMenu::~MainMenu()
{
	/*
	if (getSprite)
	{
		mpSprite = NULL;
	}
	
	if (mpAnimation)
	{
		mpAnimation = NULL;
	}
	*/
}

//Update function for the main menu
void MainMenu::update(float timePassed)
{
	getAnimation()->update(timePassed);
	setSprite(getAnimation()->getCurrentSprite());

	switch (mSelection)
	{
	case MainSelectionState::PLAY:
		getSprite()->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), SELECTOR_X, SELECTOR_Y_1, 0);
		break;
	case MainSelectionState::HELP:
		getSprite()->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), SELECTOR_X, SELECTOR_Y_2, 0);
		break;
	case MainSelectionState::CREDITS:
		getSprite()->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), SELECTOR_X, SELECTOR_Y_3, 0);
		break;
	case MainSelectionState::QUIT:
		getSprite()->draw(*gpGameApp->getGraphicsSystem()->getBackBuffer(), SELECTOR_X, SELECTOR_Y_4, 0);
		break;
	}
}