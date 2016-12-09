#pragma once

#include "Menu.h"

//Enum for the main menu selection
enum MainSelectionState
{
	PLAY,
	HELP,
	QUIT
};

class MainMenu : public Menu
{
private:
	MainSelectionState mSelection;
public:
	MainMenu() { mSelection = MainSelectionState::PLAY; };
	~MainMenu() {};

	void update(float timePassed);
};