#pragma once

#include "Menu.h"

const int H_SELECTOR_X = 250;
const int H_SELECTOR_Y_1 = 340;

//Enum for the help menu state
enum HelpSelectionState
{
	RETURN_MENU
};

class HelpMenu : public Menu
{
private:
	HelpSelectionState mSelection;

public:
	HelpMenu() { mSelection = HelpSelectionState::RETURN_MENU; };
	~HelpMenu();

	void update(float timePassed);

	inline void setSelection(HelpSelectionState select) { mSelection = select; };
	inline HelpSelectionState getSelection() { return mSelection; };
};