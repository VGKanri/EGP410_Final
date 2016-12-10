#pragma once

#include <allegro5/allegro.h>
#include <vector>
#include <map>
#include "Trackable.h"
#include "GraphicsSystem.h"

class Grid;
class GraphicsBuffer;
class Sprite;

class GridVisualizer:public Trackable
{
public:
	GridVisualizer( Grid* pGrid, bool inEditor);
	~GridVisualizer();

	void switchGrid(Grid* pGrid);
	void addColor( int index, const ALLEGRO_COLOR& color );
	void removeAllEntriesOfColor( const ALLEGRO_COLOR& color );
	void removeEntry( int index, const ALLEGRO_COLOR& color );
	void setModified() { mDirty = true; };
	void draw( GraphicsBuffer& dest );
	void clear();
private:
	void refresh();

	Grid* mpGrid;
	//key is color, vector contains all indices to be colored that color
	std::map< ALLEGRO_COLOR, std::vector<int>, AllegroColorCompare > mColormap;

	bool mDirty;
	bool mInEditor;

	//color constants, might change eventually
	const ALLEGRO_COLOR& FLOOR_COLOR = al_map_rgb(255, 255, 255);
	const ALLEGRO_COLOR& WALL_COLOR = al_map_rgb(0,0,0);
	const ALLEGRO_COLOR& PLAYER_COLOR = al_map_rgb(66, 134, 244);//blue
	const ALLEGRO_COLOR& ENEMY_COLOR = al_map_rgb(244, 66, 66); //red
	const ALLEGRO_COLOR& CANDY_COLOR = al_map_rgb(244, 66, 233); //pink
	const ALLEGRO_COLOR& DOOR_1_COLOR = al_map_rgb(131, 244, 66); //different shades of green for the doors
	const ALLEGRO_COLOR& DOOR_2_COLOR = al_map_rgb(66, 244, 69);
	const ALLEGRO_COLOR& DOOR_3_COLOR = al_map_rgb(66, 244, 131);
	const ALLEGRO_COLOR& DOOR_4_COLOR = al_map_rgb(66, 244, 170);

	//tile sprites
	Sprite* mpWallSprite;
	Sprite* mpFloorSprite;
	Sprite* mpCoinSprite;
};