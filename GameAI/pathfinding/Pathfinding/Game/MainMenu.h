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

	//Animation for the selector
	Animation* mpAnimation;
	Sprite* mpSprite;
public:
	MainMenu() { mSelection = MainSelectionState::PLAY; };
	~MainMenu();

	inline void setSelection(MainSelectionState select) { mSelection = select; };
	inline MainSelectionState getSelection() { return mSelection; };

	inline void setAnimation(Animation* anim) { mpAnimation = anim; };
	inline void setSprite(Sprite* sprite) { mpSprite = sprite; };

	void update(float timePassed);
};