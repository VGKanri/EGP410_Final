#include <allegro5/allegro.h>
#include "Game.h"
#include "GameApp.h"
#include "GameMessageManager.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "InputManager.h"
#include "GraphicsBufferManager.h"
#include "SoundManager.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"
#include "Grid.h"
#include "GridGraph.h"
#include "Connection.h"
#include "Path.h"
#include "AStar.h"
#include "Dijkstra.h"
#include "Pathfinder.h"
#include "GridPathfinder.h"
#include "GridVisualizer.h"
#include "DebugDisplay.h"
#include "PathfindingDebugContent.h"
#include "UnitManager.h"

#include <fstream>
#include <sstream>
#include <vector>

GameApp* gpGameApp = NULL;

const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;
const int GRID_SQUARE_SIZE = 32;

GameApp::GameApp()
:mpMessageManager(NULL)
,mpGrid()
,mpGridGraph()
,mpPathfinder(NULL)
,mpDebugDisplay(NULL)
{
	mPtr = make_shared<float>(5.0f);
	mLoopTargetTime = LOOP_TARGET_TIME;
	mCurrentRoom = 0;
}

GameApp::~GameApp()
{
	cleanup();
}

void GameApp::changePathfindType(PathfindType type)
{
	switch(type)
	{
	case DIJKSTRA:
		mpPathfinder = mpDijkstra;
		mpDebugDisplay->changePathfinderData(mpDijkstra);
		mPathfindType = DIJKSTRA;
		break;
	case ASTAR:
		mpPathfinder = mpAStar;
		mpDebugDisplay->changePathfinderData(mpAStar);
		mPathfindType = ASTAR;
		break;
	}
}

void GameApp::setRoomLinks()
{
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		if (mpGrid[i]->searchForValue(DOOR_1))
		{
			for (int j = 0; j < MAP_SIZE; ++j)
			{
				if (j != i && mpGrid[j]->searchForValue(DOOR_1))
				{
					mpGrid[i]->setLink(DOOR_1, mpGrid[j]);
				}
			}
		}

		if (mpGrid[i]->searchForValue(DOOR_2))
		{
			for (int j = 0; j < MAP_SIZE; ++j)
			{
				if (j != i && mpGrid[j]->searchForValue(DOOR_2))
				{
					mpGrid[i]->setLink(DOOR_2, mpGrid[j]);
				}
			}
		}

		if (mpGrid[i]->searchForValue(DOOR_3))
		{
			for (int j = 0; j < MAP_SIZE; ++j)
			{
				if (j != i && mpGrid[j]->searchForValue(DOOR_3))
				{
					mpGrid[i]->setLink(DOOR_3, mpGrid[j]);
				}
			}
		}

		if (mpGrid[i]->searchForValue(DOOR_4))
		{
			for (int j = 0; j < MAP_SIZE; ++j)
			{
				if (j != i && mpGrid[j]->searchForValue(DOOR_4))
				{
					mpGrid[i]->setLink(DOOR_4, mpGrid[j]);
				}
			}
		}
	}
}

void GameApp::changeCurrentRoom(Grid* pGrid)
{
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		if (pGrid == mpGrid[i])
		{
			mCurrentRoom = i;
		}
	}
}

bool GameApp::init()
{
	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	//load buffers
	mpGraphicsBufferManager->loadBuffer(BACKGROUND_ID, "../Assets/background.png");
	mpGraphicsBufferManager->loadBuffer(PLAYER_SPRITE_ID, "../Assets/rocket.png");
	mpGraphicsBufferManager->loadBuffer(ENEMY_SPRITE_ID, "Serguei.png");
	mpGraphicsBufferManager->loadBuffer(WALL_SPRITE_ID, "../Assets/wall.png");
	mpGraphicsBufferManager->loadBuffer(FLOOR_SPRITE_ID, "../Assets/floor.png");
	mpGraphicsBufferManager->loadBuffer(COIN_SPRITE_ID, "../Assets/coin.png");
	mpGraphicsBufferManager->loadBuffer(DOOR_SPRITE_ID, "../Assets/door.png");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer(BACKGROUND_ID);
	GraphicsBuffer* pPlayerBuffer = mpGraphicsBufferManager->getBuffer(PLAYER_SPRITE_ID);
	GraphicsBuffer* pEnemyBuffer = mpGraphicsBufferManager->getBuffer(ENEMY_SPRITE_ID);

	if (pBackGroundBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight());
	}

	if (pPlayerBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(PLAYER_SPRITE_ID, pPlayerBuffer, 0, 0, pPlayerBuffer->getWidth(), pPlayerBuffer->getHeight());
	}

	if (pEnemyBuffer != NULL)
	{
		mpSpriteManager->createAndManageSprite(ENEMY_SPRITE_ID, pEnemyBuffer, 0, 0, pEnemyBuffer->getWidth(), pEnemyBuffer->getHeight());
	}

	//load managers
	mpInputManager = new InputManager();
	mpInputManager->init();

	mpMessageManager = new GameMessageManager();

	//create and load the Grid, GridBuffer, and GridRenderer
	std::ifstream fs;
	std::stringstream ss;

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		mpGrid[i] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
		
		ss << FILE_NAME << i + 1 << ".txt";
		fs.open(ss.str());
		mpGrid[i]->load(fs);
		fs.close();
		ss.str(""); //clear string stream
		
		//generate coins when initting grid
		mpGrid[i]->generateCoins();
	}

	setRoomLinks(); //vital for room transferring

	mpGridVisualizer = new GridVisualizer( mpGrid[0], false);

	//create the GridGraph for pathfinding
	for (int i = 0; i < MAP_SIZE; ++i)
	{
		mpGridGraph[i] = new GridGraph(mpGrid[i]);
		mpGridGraph[i]->init(); //inits nodes and connections
	}

	//init sound manager
	mpSoundManager = new SoundManager();
	mpSoundManager->init();
	mpSoundManager->playSong(BATTLE_THEME_KEY);

	//init pathfinders
	mpDijkstra = new Dijkstra(mpGridGraph[0]);
	mpAStar = new AStar(mpGridGraph[0]);

	mpUnitManager = new UnitManager();

	//set default pathfinder to Dijkstra
	mpPathfinder = mpDijkstra;
	mPathfindType = DIJKSTRA;

	//spawn player at the spawn player block of the grid
	mpUnitManager->addUnit(mpSpriteManager->getSprite(PLAYER_SPRITE_ID), getGrid()->getULCornerOfSquare(getGrid()->getIndexOfPlayerSpawn()), Vector2D(0, 0), mPtr, mPtr, mPtr, 1.0f, "player", true);
	mpUnitManager->addUnit(mpSpriteManager->getSprite(ENEMY_SPRITE_ID), Vector2D(200, 200), Vector2D(0, 0), mPtr, mPtr, mPtr, 1.0f, "enemy", false);

	//debug display
	PathfindingDebugContent* pContent = new PathfindingDebugContent( mpPathfinder );
	mpDebugDisplay = new DebugDisplay( Vector2D(0,12), pContent );

	mpMasterTimer->start();
	return true;
}

void GameApp::cleanup()
{
	delete mpMessageManager;
	mpMessageManager = NULL;

	delete mpSoundManager;
	mpSoundManager = NULL;

	delete mpInputManager;
	mpInputManager = NULL;

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		delete mpGrid[i];
		mpGrid[i] = NULL;
	}

	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	for (int i = 0; i < MAP_SIZE; ++i)
	{
		delete mpGridGraph[i];
		mpGridGraph[i] = NULL;
	}

	delete mpDijkstra;
	mpDijkstra = NULL;

	delete mpAStar;
	mpAStar = NULL;

	delete mpDebugDisplay;
	mpDebugDisplay = NULL;

	delete mpUnitManager;
	mpUnitManager = NULL;
}

void GameApp::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void GameApp::processLoop()
{
	//get back buffer
	GraphicsBuffer* pBackBuffer = mpGraphicsSystem->getBackBuffer();
	//copy to back buffer
	mpGridVisualizer->draw(*pBackBuffer);
#ifdef VISUALIZE_PATH
	//show pathfinder visualizer
    //mpPathfinder->drawVisualization(mpGrid[mCurrentRoom], pBackBuffer);
#endif

	mpDebugDisplay->draw(pBackBuffer);

	mpMessageManager->processMessagesForThisframe();

	mpInputManager->update();

	mpUnitManager->update(LOOP_TARGET_TIME / 1000.0f);
	//should be last thing in processLoop
	Game::processLoop();
}
	

bool GameApp::endLoop()
{
	return Game::endLoop();
}
