#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

/* This class handles drawing the text needed
	for the user to use the editor correctly.
	This also might handle the help feature*/

const std::string HELP_PNG_PATH = "../Assets/HelpMenu.png";

class EditorGUI : public Trackable
{
public:
	EditorGUI();
	~EditorGUI();

	void setTileTypeText(int tileType);
	void setRoomNumText(int roomNum);
	inline void toggleHelpMenu() { mDrawHelpMenu = !mDrawHelpMenu; };

	void draw();

private:
	ALLEGRO_FONT* mpFont;
	ALLEGRO_BITMAP* mpHelpPNG;

	bool mDrawHelpMenu;

	Vector2D mHelpPNGPos;

	Vector2D mTileTextPos;
	Vector2D mRoomNumTextPos;
	Vector2D mHelpTextPos;
	Vector2D mExitTextPos;

	std::string mTileTypeText;
	std::string mRoomNumText;
	std::string mTileBaseText;
	std::string mRoomBaseText;
	std::string mHelpText;
	std::string mExitText;
};