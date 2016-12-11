#pragma once

/*Game - class to hold all game related info.

Dean Lawson
Champlain College
2011
*/

#include "Game.h"
#include <memory>

//forward declarations
class GraphicsBuffer;
class Sprite;
class KinematicUnit;
class GameMessageManager;
class Grid;
class GridVisualizer;
class GridGraph;
class GridPathfinder;
class DebugDisplay;
class InputManager;
class UnitManager;
class SoundManager;

const float LOOP_TARGET_TIME = 16.6f;//how long should each frame of execution take? 30fps = 33.3ms/frame

const std::string FILE_NAME = "../Game/pathgrid";

const int MAP_SIZE = 4;

enum PathfindType
{
	DIJKSTRA,
	ASTAR
};

enum GameState
{
	MAIN_MENU,
	PLAYING,
	HELP_MENU
};

class GameApp: public Game
{
public:
	GameApp();
	~GameApp();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	//accessors
	inline GameMessageManager* getMessageManager() { return mpMessageManager; };
	inline SoundManager* getSoundManager() { return mpSoundManager; };
	inline GridVisualizer* getGridVisualizer() { return mpGridVisualizer; };
	inline GridPathfinder* getPathfinder() { return mpPathfinder; };
	inline Grid* getGrid(int gridNum) { return mpGrid[gridNum]; };
	inline Grid* getGrid() { return mpGrid[mCurrentRoom]; };
	inline GridGraph* getGridGraph(int gridNum) { return mpGridGraph[gridNum]; };
	inline GridGraph* getGridGraph() { return mpGridGraph[0]; };
	inline InputManager* getInputManager() { return mpInputManager; };
	inline const PathfindType getPathfindType() const { return mPathfindType; };
	inline UnitManager* getUnitManager() { return mpUnitManager; };
	inline GameState getState() { return mState; };
	inline void setState(GameState state) { mState = state; };
	//inline void setPtr(float ptr) { mPtr = ptr; };

	void changePathfindType(PathfindType type); //changes mpPathfinder to match pathfindertype that is passed in
	void setRoomLinks(); //reads rooms to set appropriate room links
	void changeCurrentRoom(Grid* pGrid); //changes the mCurrentRoom variable to match the current grid

private:
	GameMessageManager* mpMessageManager;
	SoundManager* mpSoundManager;
	Grid* mpGrid[MAP_SIZE];
	GridVisualizer* mpGridVisualizer;
	GridGraph* mpGridGraph[MAP_SIZE];

	DebugDisplay* mpDebugDisplay;
	InputManager* mpInputManager;

	GridPathfinder* mpPathfinder;
	GridPathfinder* mpDijkstra;
	GridPathfinder* mpAStar;

	UnitManager* mpUnitManager;

	PathfindType mPathfindType;

	int mCurrentRoom;

	//Shared pointers
	std::shared_ptr<float> mPtr;

	GameState mState;
};

