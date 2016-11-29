#pragma once

#include "DebugContent.h"

class GridPathfinder;

class PathfindingDebugContent:public DebugContent
{
public:
	PathfindingDebugContent( GridPathfinder* pPathfinder );
	~PathfindingDebugContent(){};

	std::string getDebugString();

	void setPathfinder(GridPathfinder* pPathFinder);

private:
	GridPathfinder* mpPathfinder;
};