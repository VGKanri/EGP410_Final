#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "Grid.h"
#include "GridVisualizer.h"
#include "Path.h"
#include "GameApp.h"
#include "GraphicsBuffer.h"

GridPathfinder::GridPathfinder( GridGraph* pGraph )
:Pathfinder(pGraph)
,mTimeElapsed(0.0)
{
#ifdef VISUALIZE_PATH
	mpVisualizer = NULL;
#endif
}

GridPathfinder::~GridPathfinder()
{
#ifdef VISUALIZE_PATH
	delete mpVisualizer;
#endif
}

#ifdef VISUALIZE_PATH
void GridPathfinder::drawVisualization( Grid* pGrid, GraphicsBuffer* pDest )
{

	//this is dean's code, handles drawing the nodes that were searched
	if (mpVisualizer == NULL)
	{
		mpVisualizer = new GridVisualizer(pGrid);
	}
	else
	{
		mpVisualizer->clear();
	}

	//change path color depending on search algorithm being run
	static ALLEGRO_COLOR pathColor;
	if (gpGameApp->getPathfindType() == DIJKSTRA)
	{
		pathColor = al_map_rgb(255, 64, 64);
	}
	else
	{
		pathColor = al_map_rgb(64, 64, 255);
	}

	static ALLEGRO_COLOR startColor = al_map_rgb(1, 255, 128);
	static ALLEGRO_COLOR stopColor = al_map_rgb(255, 255, 0);

	unsigned int numNodes = mPath.getNumNodes();
	ALLEGRO_COLOR currentPathColor = pathColor;

	if (numNodes > 0)
	{
		for (unsigned int i = 1; i < numNodes-1; i++)
		{
			mpVisualizer->addColor(mPath.peekNode(i)->getId(), currentPathColor);
			float lerpVal = lerp( i, 0, numNodes );
			currentPathColor.r = 1.0f - lerpVal;
		}

		//add beginning and ending color
		mpVisualizer->addColor(mPath.peekNode(0)->getId(), startColor);
		mpVisualizer->addColor(mPath.peekNode(numNodes - 1)->getId(), stopColor);
	}

	mpVisualizer->draw(*pDest);

	drawPathCenterLines(); //draw the shortest path
}
#endif

#ifdef VISUALIZE_PATH
void GridPathfinder::drawPathCenterLines()
{
	//this handles drawing the centerlines between the nodes that make the shortest path
	float offset = gpGameApp->getGrid()->getSquareSize() / 2;

	for (int i = 0; i < mShortestPath.getNumNodes() - 1; ++i) //iterate through shortest path and draw lines in between each node
	{
		Vector2D pos1 = gpGameApp->getGrid()->getULCornerOfSquare(mShortestPath.peekNode(i)->getId());
		Vector2D pos2 = gpGameApp->getGrid()->getULCornerOfSquare(mShortestPath.peekNode(i + 1)->getId());

		al_draw_line(pos1.getX() + offset, pos1.getY() + offset, pos2.getX() + offset, pos2.getY() + offset, al_map_rgb(0, 255, 255), 5);
	}	
}
#endif
