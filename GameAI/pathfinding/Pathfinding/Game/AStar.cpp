#include "AStar.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "Grid.h"
#include "GameApp.h"
#include "Vector2D.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>
#include <cmath>

AStar::AStar(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

AStar::~AStar()
{
}

const Path& AStar::findPath(Node *pFrom, Node* pTo)
{
	gpPerformanceTracker->clearTracker("path");
	gpPerformanceTracker->startTracking("path");

	pFrom->setPrevNodeId(pFrom->getId()); //pFrom is the starting point

										  //allocate nodes to visit list and place starting node in it
	std::list<Node*> nodesToVisit;
	nodesToVisit.push_front(pFrom);

#ifdef VISUALIZE_PATH
	mVisitedNodes.clear();
	mVisitedNodes.push_back(pFrom);
#endif

	mPath.clear();
	mShortestPath.clear();

	Node* pCurrentNode = NULL;
	bool toNodeAdded = false;

	while (pCurrentNode != pTo && nodesToVisit.size() > 0)
	{
		//get current node from front of list
		pCurrentNode = nodesToVisit.front();
		//remove node from list
		nodesToVisit.pop_front();
		//add Node to Path
		mPath.addNode(pCurrentNode);

		//get the Connections for the current node
		std::vector<Connection*> connections = mpGraph->getConnections(pCurrentNode->getId());

		//add all toNodes in the connections to the "toVisit" list, if they are not already in the list
		for (unsigned int i = 0; i<connections.size(); i++)
		{
			Connection* pConnection = connections[i];
			Node* pTempToNode = connections[i]->getToNode();

			if (!toNodeAdded &&
				!mPath.containsNode(pTempToNode) &&
				find(nodesToVisit.begin(), nodesToVisit.end(), pTempToNode) == nodesToVisit.end())
			{
				pTempToNode->setPrevNodeId(pCurrentNode->getId()); //if node is added to search, save a reference to the node it connected from

				//check distance heuristic here to determine whether the node should be pushed to the front or back of the list
				if (nodesToVisit.size() > 0 && checkHeuristic(pTo, pTempToNode, nodesToVisit.front()) == true)
				{
					nodesToVisit.push_front(pTempToNode);
				}
				else
				{
					nodesToVisit.push_back(pTempToNode);
				}

				if (pTempToNode == pTo)
				{
					toNodeAdded = true;
				}

#ifdef VISUALIZE_PATH
				mVisitedNodes.push_back(pTempToNode);
#endif
			}
		}

		//goal has been reached, now iterate backwards through the nodes and their from references to determine the path		
		if (toNodeAdded)
		{
			mShortestPath.clear();
			Node* pPathNode = pTo; //start at goal

			while (!mShortestPath.containsNode(pPathNode)) //loop until path reaches starting position
			{
				mShortestPath.addNode(pPathNode); //add current node to path	
				pPathNode = gpGameApp->getGridGraph()->getNode(pPathNode->getPrevNodeId()); //set the temp node to the previous node that connected to it
			}
		}
	}

	gpPerformanceTracker->stopTracking("path");
	mTimeElapsed = gpPerformanceTracker->getElapsedTime("path");

	return mPath;

}

bool AStar::checkHeuristic(Node* pGoal, Node* pCurrent, Node* pNextToVisit) const
{
	//get positions of all nodes vital to the heuristic
	Vector2D goalPos = gpGameApp->getGrid()->getULCornerOfSquare(pGoal->getId());
	Vector2D currentPos = gpGameApp->getGrid()->getULCornerOfSquare(pCurrent->getId());
	Vector2D nextToVisitPos = gpGameApp->getGrid()->getULCornerOfSquare(pNextToVisit->getId());

	//calculate the absolute value of the distance between the goal and the current node, and the distance between
	//the goal that is going to be visited next and the goal
	float currentDistance = abs(sqrt(pow((goalPos.getX() - currentPos.getX()), 2) + pow((goalPos.getY() - currentPos.getY()), 2)));
	float nextToVisitDistance = abs(sqrt(pow((goalPos.getX() - nextToVisitPos.getX()), 2) + pow((goalPos.getY() - nextToVisitPos.getY()), 2)));

	//compare the distances, if the current distance is shorter return true, signifying to findPath
	//that the current nodes takes priority in the toBeVisited Vector
	if (currentDistance <= nextToVisitDistance)
	{
		return true;
	}
	else
	{
		return false;
	}
}