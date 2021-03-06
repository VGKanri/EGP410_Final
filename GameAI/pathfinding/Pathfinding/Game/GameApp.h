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
class MainMenu;
class HelpMenu;

const float LOOP_TARGET_TIME = 16.6f;//how long should each frame of execution take? 30fps = 33.3ms/frame

const std::string FILE_NAME = "../Game/pathgrid";

const int MAP_SIZE = 4;

enum GameState
{
	MAIN_MENU,
	PLAYING,
	HELP_MENU,
	CREDITS_MENU,
	END
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
	inline Grid* getGrid(int gridNum) { return mpGrid[gridNum]; };
	inline Grid* getGrid() { return mpGrid[mCurrentRoom]; };
	inline GridGraph* getGridGraph(int gridNum) { return mpGridGraph[gridNum]; };
	inline GridGraph* getGridGraph() { return mpGridGraph[mCurrentRoom]; };
	inline InputManager* getInputManager() { return mpInputManager; };
	inline UnitManager* getUnitManager() { return mpUnitManager; };
	inline MainMenu* getMainMenu() { return mpMainMenu; };
	inline DebugDisplay* getDebugDisplay() { return mpDebugDisplay; };

	inline GameState getState() { return mState; };
	inline void setState(GameState state) { mState = state; };
	//inline void setPtr(float ptr) { mPtr = ptr; };

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

	UnitManager* mpUnitManager;

	MainMenu* mpMainMenu;
	HelpMenu* mpHelpMenu;

	int mCurrentRoom;

	//Shared pointers
	std::shared_ptr<float> mPtr;
	std::shared_ptr<float> mMaxVel;

	GameState mState;
};

