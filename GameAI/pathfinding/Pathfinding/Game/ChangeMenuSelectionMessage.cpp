#include "ChangeMenuSelectionMessage.h"
#include "GameMessageManager.h"
#include "MainMenu.h"

ChangeMenuSelectionMessage::ChangeMenuSelectionMessage(bool increase, bool mainMenu)
:GameMessage(CHANGE_MENU_SELECTION_MESSAGE)
,mIncrease(increase)
,mMainMenu(mainMenu)
{
}

void ChangeMenuSelectionMessage::process()
{
	//If it is on the main menu
	if (mMainMenu)
	{
		if (mIncrease)
		{
			switch (gpGameApp->getMainMenu()->getSelection())
			{
			case MainSelectionState::PLAY:
				gpGameApp->getMainMenu()->setSelection(MainSelectionState::HELP);
				break;
			case MainSelectionState::HELP:
				gpGameApp->getMainMenu()->setSelection(MainSelectionState::QUIT);
				break;
			case MainSelectionState::QUIT:
				gpGameApp->getMainMenu()->setSelection(MainSelectionState::PLAY);
				break;
			}
		}
		else
		{
			switch (gpGameApp->getMainMenu()->getSelection())
			{
			case MainSelectionState::PLAY:
				gpGameApp->getMainMenu()->setSelection(MainSelectionState::QUIT);
				break;
			case MainSelectionState::HELP:
				gpGameApp->getMainMenu()->setSelection(MainSelectionState::PLAY);
				break;
			case MainSelectionState::QUIT:
				gpGameApp->getMainMenu()->setSelection(MainSelectionState::HELP);
				break;
			}
		}
	}
	std::cout << gpGameApp->getMainMenu()->getSelection() << std::endl;
	//If it is on the help menu
}