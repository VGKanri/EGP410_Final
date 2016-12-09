#pragma once

#include "Menu.h"

//Enum for the help menu state
enum HelpSelectionState
{
	RETURN_MENU,
	RETURN_GAME
};

class HelpMenu : public Menu
{
private:
	HelpSelectionState mSelection;

public:
	HelpMenu() { mSelection = HelpSelectionState::RETURN_MENU; };
	~HelpMenu() {};

	void update(float timePassed);

	//Setter for the selection state
	inline void setSelection(HelpSelectionState state) { mSelection = state; };
};