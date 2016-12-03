#include "Wall.h"

Wall::Wall(float x1, float y1, float x2, float y2, BounceType bounceType)
{
	minX = x1;
	minY = y1;
	maxX = x2;
	maxY = y2;

	mBounceType = bounceType;

	mHitbox = Hitbox(x1, y1, x2, y2);
}

Wall::~Wall()
{

}

void Wall::draw()
{
	al_draw_filled_rectangle(minX, minY, maxX, maxY, al_map_rgb(0, 0, 0));
	mHitbox.draw();
}