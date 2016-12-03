#include "WallManager.h"

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
	mWallList.push_back(new Wall(0, 0, 50, 768, HORIZONTAL)); //left wall
	mWallList.push_back(new Wall(0, 0, 1024, 50, VERTICAL)); //top wall
	mWallList.push_back(new Wall(0, 718, 1024, 768, VERTICAL)); //bottom wall
	mWallList.push_back(new Wall(974, 0, 1024, 768, HORIZONTAL)); //right wall
}

void WallManager::update()
{
	for (auto iter : mWallList)
	{
		iter->draw();
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