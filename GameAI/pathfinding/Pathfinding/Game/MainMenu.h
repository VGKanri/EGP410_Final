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

	inline void setSelection(MainSelectionState select) { mSelection = select; };
	inline MainSelectionState getSelection() { return mSelection; };

	void update(float timePassed);
};