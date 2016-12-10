#include "WallManager.h"
#include "GameApp.h"

WallManager::WallManager()
{

}

WallManager::~WallManager()
{
	cleanUp();	
}

//this basically sets up the inital walls. A bit sloppy but does the trick
void WallManager::init()
{
}

void WallManager::update()
{
	for (auto iter : mWallList)
	{
		//iter->getHitbox().draw();
	}
}

void WallManager::cleanUp()
{
	for (auto iter : mWallList)
	{
		delete iter;
	}

	mWallList.clear();
}

Wall* WallManager::getWall(int index)
{
	return mWallList[index];
}