#pragma once

#include "GameMessage.h"
#include "GameApp.h"

//This message is fired when the user attempts to change the selection on the main or help menu
class ChangeMenuSelectionMessage : public GameMessage
{
public:
	ChangeMenuSelectionMessage(bool increase, bool mainMenu);
	~ChangeMenuSelectionMessage() {};

	void process();

private:
	bool mIncrease, mMainMenu;
};