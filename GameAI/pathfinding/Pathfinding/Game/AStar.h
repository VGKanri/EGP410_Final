#pragma once

#include "GridPathfinder.h"

class Path;
class Graph;

/* An implementation of the A* algorithm. The implementation is basically going
to be the same as Dijkstra but with a heuristic that changes the order of nodes
to check based on their priority*/

class AStar :public GridPathfinder
{
public:
	AStar(Graph* pGraph);
	~AStar();

	const Path& findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!

private:
	bool checkHeuristic(Node* pGoal, Node* pCurrent, Node* pNextToVisit) const; //The Heuristic in question will be Euclidean Distance to the goal
};