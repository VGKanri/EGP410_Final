#include "Wall.h"

Wall::Wall(float x1, float y1, float x2, float y2)
{
	minX = x1;
	minY = y1;
	maxX = x2;
	maxY = y2; 

	mHitbox = Hitbox(x1, y1, x2, y2);
}

Wall::~Wall()
{

}