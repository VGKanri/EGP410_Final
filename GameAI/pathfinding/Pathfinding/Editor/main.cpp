/*main.cpp
 *	Editor for pathfinding project
 *
 *	Dean Lawson
 *	Champlain College
 *	2011
 *
 */
#define ALLEGRO_USE_CONSOLE //allows the console to be used
#include <allegro5/allegro.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <fstream>
#include <iostream>

#include "Game.h"
#include "Editor.h"
#include "GraphicsSystem.h"
#include "GraphicsBuffer.h"
#include "Sprite.h"
#include "Timer.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "PerformanceTracker.h"
#include "MemoryTracker.h"

const std::string FILE_NAME = "../Game/pathgrid.txt";

int main(void)
{
	//create the Editor
	gpGame = new Editor();

	gpGame->init();

	bool shouldExit = false;

	while( !shouldExit )
	{
		gpGame->beginLoop();
		gpGame->processLoop();
		shouldExit = gpGame->endLoop();
	}

	//cleanup
	gpGame->cleanup();
	delete gpGame;
	gMemoryTracker.reportAllocations( std::cout );

	system("pause");

	return 0;
}

