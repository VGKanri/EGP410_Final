#pragma once

#include "GridPathfinder.h"

class Path;
class Graph;

/* An implementation of the Dijkstra algorithm. Heavily borrows of of 
	DepthFirstPathfinder and makes modifications to allow nodes to retrace their
	steps when the goal is eventually found.*/

class Dijkstra :public GridPathfinder
{
public:
	Dijkstra(Graph* pGraph);
	~Dijkstra();

	const Path& findPath(Node* pFrom, Node* pTo);//make sure to delete the path when you are done!

private:
};