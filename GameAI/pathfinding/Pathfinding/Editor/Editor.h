#pragma once

#include "Game.h"
#include <fstream>

/*Editor - class to hold all application related info.

Dean Lawson
Champlain College
2011
*/

/*
Gabriel Pereyra, building on this editor code to make it more complex, 
for example, supporting different tile types and rooms

NOTE TO SELF - For sake of having things work, many things using mpGrid will have to use mpGrid[0]
since it's the first room. This will be adapted later to work with a more dynamic room structure.
*/

//forward declarations
class GraphicsBuffer;
class Sprite;
class Grid;
class GridVisualizer;
class GraphicsBuffer;
class EditorInputManager;

const float LOOP_TARGET_TIME = 33.3f;//how long should each frame of execution take? 30fps = 33.3ms/frame
const int ROOM_AMOUNT = 4;

class Editor: public Game
{
public:
	Editor();
	virtual ~Editor();

	inline Grid* getGrid() { return mpGrid[0]; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };

	inline int getTileType() const { return mTileType; };
	inline int setTileType(const int TileType) { mTileType = TileType; };

	inline int getCurrentRoom() const { return mCurrentRoom; };
	inline int setCurrentRoom(int newRoom) { mCurrentRoom = newRoom; };

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	void saveGrid( std::ofstream& theStream );
	void loadGrid( std::ifstream& theStream );

private:
	Grid* mpGrid[ROOM_AMOUNT]; //array of rooms
	GridVisualizer* mpGridVisualizer;
	EditorInputManager* mpInputManager;

	int mTileType; //keeps track of current tile type being drawn
	int mCurrentRoom; //keeps track of what room you are currently editing
};