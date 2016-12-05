#include "EditorGUI.h"
#include "Grid.h"

#include <allegro5/allegro_ttf.h>

EditorGUI::EditorGUI()
{
	mTileTypeText = "Wall";
	mRoomNumText = "Room 1";
	mTileBaseText = "Current Tile Type: ";
	mRoomBaseText = "Current Room: ";
	mHelpText = "'H' - Help Menu";

	mTileTextPos = Vector2D(25, 25);
	mRoomNumTextPos = Vector2D(25, mTileTextPos.getY() + 25);
	mHelpTextPos = Vector2D(999, 25);

	//actually load the font
	mpFont = al_load_ttf_font("cour.ttf", 20, 0);
	if (mpFont == NULL)
	{
		printf("ttf font file not loaded properly!\n");
		assert(0);
	}
}

EditorGUI::~EditorGUI()
{
	al_destroy_font(mpFont);
}

//apologies for the ugly switch statement,
//adjusts the string to match with the constants
//in grid.h
void EditorGUI::setTileTypeText(int tileType)
{
	switch (tileType)
	{
	case BLOCKING_VALUE:
		mTileTypeText = "Wall";
		break;
	case PLAYER_SPAWN:
		mTileTypeText = "Player Spawn";
		break;
	case ENEMY_SPAWN:
		mTileTypeText = "Enemy Spawn";
		break;
	case CANDY_SPAWN:
		mTileTypeText = "Candy Spawn";
		break;
	case DOOR_1:
		mTileTypeText = "Door 1";
		break;
	case DOOR_2:
		mTileTypeText = "Door 2";
		break;
	case DOOR_3:
		mTileTypeText = "Door 3";
		break;
	case DOOR_4:
		mTileTypeText = "Door 4";
		break;
	}
}

//the numbers in this switch statement correspond to the
//room's position in the room array
void EditorGUI::setRoomNumText(int roomNum)
{
	switch (roomNum)
	{
	case 0:
		mRoomNumText = "Room 1";
		break;
	case 1:
		mRoomNumText = "Room 2";
		break;
	case 2:
		mRoomNumText = "Room 3";
		break;
	case 3:
		mRoomNumText = "Room 4";
		break;
	}
}

void EditorGUI::draw()
{
	std::string tileDisplay = mTileBaseText + mTileTypeText;
	std::string roomDisplay = mRoomBaseText + mRoomNumText;

	al_draw_text(mpFont, al_map_rgb(255, 255, 255), mTileTextPos.getX(), mTileTextPos.getY(), ALLEGRO_ALIGN_LEFT, tileDisplay.c_str());
	al_draw_text(mpFont, al_map_rgb(255, 255, 255), mRoomNumTextPos.getX(), mRoomNumTextPos.getY(), ALLEGRO_ALIGN_LEFT, roomDisplay.c_str());
	al_draw_text(mpFont, al_map_rgb(255, 255, 255), mHelpTextPos.getX(), mHelpTextPos.getY(), ALLEGRO_ALIGN_RIGHT, mHelpText.c_str());
}