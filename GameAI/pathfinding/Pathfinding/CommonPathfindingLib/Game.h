#pragma once

/* Game - base class for actual application class

	Dean Lawson
	Champlain College
	2011
*/
#include <Trackable.h>
#include <Timer.h>
#include "Defines.h"

class MemoryTracker;
class PerformanceTracker;
class GraphicsSystem;
class GraphicsBuffer;
class GraphicsBufferManager;
class SpriteManager;
class Game;
class GameApp;
struct ALLEGRO_FONT;

extern PerformanceTracker* gpPerformanceTracker;
extern Game* gpGame;
extern GameApp* gpGameApp;


const IDType BACKGROUND_SPRITE_ID = 0;
const IDType PLAYER_SPRITE_ID = 1;
const IDType ENEMY_SPRITE_ID = 2;
const IDType WALL_SPRITE_ID = 3;
const IDType FLOOR_SPRITE_ID = 4;
const IDType COIN_SPRITE_ID = 5;
const IDType DOOR_SPRITE_ID = 6;
const IDType MAIN_MENU_ID = 7;
const IDType HELP_MENU_ID = 8;
const IDType CREDITS_ID = 9;
const IDType CANDY_ID = 10;
const IDType LOSE_ID = 11;

class Game:public Trackable
{
public:
	Game();
	virtual ~Game();

	virtual bool init();
	virtual void cleanup();

	//game loop
	virtual void beginLoop();
	virtual void processLoop();
	virtual bool endLoop();

	inline GraphicsSystem* getGraphicsSystem() const { return mpGraphicsSystem; };
	inline GraphicsBufferManager* getGraphicsBufferManager() const { return mpGraphicsBufferManager; };
	inline SpriteManager* getSpriteManager() const { return mpSpriteManager; };
	inline Timer* getMasterTimer() const { return mpMasterTimer; };
	inline double getCurrentTime() const { return mpMasterTimer->getElapsedTime(); };
	inline ALLEGRO_FONT* getFont() const { return mpFont; };
	inline void markForExit() { mShouldExit = true; };

protected:
	GraphicsSystem* mpGraphicsSystem;
	GraphicsBufferManager* mpGraphicsBufferManager;
	SpriteManager* mpSpriteManager;
	Timer* mpLoopTimer;
	Timer* mpMasterTimer;
	float mLoopTargetTime;
	bool mShouldExit;

	//should be somewhere else
	ALLEGRO_FONT* mpFont;

};

float genRandomBinomial();//range -1:1 from "Artificial Intelligence for Games", Millington and Funge
float genRandomFloat();//range 0:1 from "Artificial Intelligence for Games", Millington and Funge
float mapRotationToRange( float rotation, float low, float high );
float lerp(int value, int start, int end);//returns float representing how far value is between start and end