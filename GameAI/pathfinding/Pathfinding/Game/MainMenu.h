#pragma once

#include "Menu.h"
#include "Animation.h"
#include "Sprite.h"

const int SELECTOR_X = 250;
const int SELECTOR_Y_1 = 45;
const int SELECTOR_Y_2 = 150;
const int SELECTOR_Y_3 = 240;
const int SELECTOR_Y_4 = 330;

//Enum for the main menu selection
enum MainSelectionState
{
	PLAY,
	HELP,
	CREDITS,
	QUIT
};

class MainMenu : public Menu
{
private:
	MainSelectionState mSelection;
	
public:
	MainMenu() { mSelection = MainSelectionState::PLAY; };
	~MainMenu();

	void update(float timePassed);

	inline void setSelection(MainSelectionState select) { mSelection = select; };
	inline MainSelectionState getSelection() { return mSelection; };
};