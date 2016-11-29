#include "Dijkstra.h"
#include "Path.h"
#include "Connection.h"
#include "GridGraph.h"
#include "GameApp.h"
#include <PerformanceTracker.h>
#include <list>
#include <vector>
#include <algorithm>

Dijkstra::Dijkstra(Graph* pGraph)
	:GridPathfinder(dynamic_cast<GridGraph*>(pGraph))
{
}

Dijkstra::~Dijkstra()
{
}

const Path& Dijkstra::findPath(Node *pFrom, Node* pTo)
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

				nodesToVisit.push_back(pTempToNode);//uncomment me for breadth-first search
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