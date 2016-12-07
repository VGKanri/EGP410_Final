#include <fstream>
#include <allegro5/allegro_primitives.h>

#include "Game.h"
#include "Editor.h"
#include "EditorInputManager.h"
#include "EditorGUI.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "GraphicsBufferManager.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "Sprite.h"
#include "SpriteManager.h"
#include "Vector2D.h"

using namespace std;

const int GRID_SQUARE_SIZE = 32;
const IDType BACKGROUND_ID = ENDING_SEQUENTIAL_ID + 1;

Editor::Editor()
:Game()
,mpGrid()
,mpGridVisualizer(NULL)
{
}

Editor::~Editor()
{
	//clean up is already called in main
	//cleanup();
}

bool Editor::init()
{
	//these variables are used to keep track of what room or tile to edit
	mCurrentRoom = 0;
	mTileType = BLOCKING_VALUE;

	bool retVal = Game::init();
	if( retVal == false )
	{

		return false;
	}

	for (int i = 0; i < ROOM_AMOUNT; ++i)
	{
		mpGrid[i] = new Grid(mpGraphicsSystem->getWidth(), mpGraphicsSystem->getHeight(), GRID_SQUARE_SIZE);
	}
	
	mpGridVisualizer = new GridVisualizer(mpGrid[0]);

	mpEditorGUI = new EditorGUI();

	mpInputManager = new EditorInputManager();
	mpInputManager->init();

	//load buffers
	mpGraphicsBufferManager->loadBuffer( BACKGROUND_ID, "wallpaper.bmp");

	//setup sprites
	GraphicsBuffer* pBackGroundBuffer = mpGraphicsBufferManager->getBuffer( BACKGROUND_ID );
	if( pBackGroundBuffer != NULL )
	{
		mpSpriteManager->createAndManageSprite( BACKGROUND_SPRITE_ID, pBackGroundBuffer, 0, 0, pBackGroundBuffer->getWidth(), pBackGroundBuffer->getHeight() );
	}
	
	mpMasterTimer->start();
	return true;
}

void Editor::cleanup()
{
	delete mpGridVisualizer;
	mpGridVisualizer = NULL;

	delete mpEditorGUI;
	mpEditorGUI = NULL;

	for (int i = 0; i < ROOM_AMOUNT; ++i)
	{
		delete mpGrid[i];
		mpGrid[i] = NULL;
	}

	delete mpInputManager;
	mpInputManager = NULL;
}

void Editor::beginLoop()
{
	//should be the first thing done
	Game::beginLoop();
}

void Editor::processLoop()
{
	mpInputManager->update();

	//copy to back buffer
	mpGridVisualizer->draw(*(mpGraphicsSystem->getBackBuffer()));
	mpEditorGUI->draw();

	//should be last thing in processLoop
	Game::processLoop();
}

bool Editor::endLoop()
{
	return Game::endLoop();
}

void Editor::saveGrid( ofstream& theStream, int roomNum )
{
	mpGrid[roomNum]->save( theStream );
}

void Editor::loadGrid( std::ifstream& theStream, int roomNum )
{
	mpGrid[roomNum]->load(theStream);
}
