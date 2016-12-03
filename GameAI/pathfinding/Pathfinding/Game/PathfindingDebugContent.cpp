#include "PathfindingDebugContent.h"
#include "GridPathfinder.h"
#include "Path.h"
#include <sstream>

using namespace std;

PathfindingDebugContent::PathfindingDebugContent( GridPathfinder* pPathfinder )
	:mpPathfinder(pPathfinder)
{
}

string PathfindingDebugContent::getDebugString()
{
	stringstream theStream;

#ifdef VISUALIZE_PATH
	theStream << "Pathlength:"<< mpPathfinder->mShortestPath.getNumNodes();
	
	theStream << "  Num Nodes Processed:" << mpPathfinder->mPath.getNumNodes();
#endif
	theStream << "  Elapsed Time:" << mpPathfinder->mTimeElapsed;
	return theStream.str();
}

void PathfindingDebugContent::setPathfinder(GridPathfinder* pPathfinder)
{
	mpPathfinder = pPathfinder;
}

