#ifndef WALL_MANAGER
#define WALL_MANAGER

#include "Trackable.h"
#include "Wall.h"

#include <vector>

class WallManager : public Trackable
{
public:
	WallManager();
	~WallManager();

	void init();
	void update();
	void cleanUp();

	Wall* getWall(int index);
	inline int getNumOfWalls() { return mWallList.size(); };

private:
	std::vector<Wall*> mWallList; 
};

#endif