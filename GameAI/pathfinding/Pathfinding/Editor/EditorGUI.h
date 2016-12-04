#pragma once

#include "Trackable.h"
#include "Vector2D.h"
#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

/* This class handles drawing the text needed
	for the user to use the editor correctly.
	This also might handle the help feature*/

class EditorGUI : public Trackable
{
public:
	EditorGUI();
	~EditorGUI();

	void setTileTypeText(int tileType);
	void setRoomNumText(int roomNum);

	void draw();

private:
	ALLEGRO_FONT* mpFont;

	Vector2D mTileTextPos;
	Vector2D mRoomNumTextPos;
	Vector2D mHelpTextPos;

	std::string mTileTypeText;
	std::string mRoomNumText;
	std::string mTileBaseText;
	std::string mRoomBaseText;
	std::string mHelpText;
};