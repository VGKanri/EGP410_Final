#ifndef WALL_H
#define WALL_H

#include "Trackable.h"
#include "Hitbox.h"

#include <allegro5\allegro_primitives.h>

enum BounceType
{
	VERTICAL,
	HORIZONTAL
};

class Wall : public Trackable
{
public:
	Wall(float x1, float y1, float x2, float y2, BounceType verticalWall);
	~Wall();

	inline Hitbox& getHitbox() { return mHitbox; };
	inline BounceType getBounceType() { return mBounceType; }; //gets flag that determines how a unit should bounch upon collision with the wall
	void draw();

private:
	Hitbox mHitbox;

	float minX;
	float minY;
	float maxX;
	float maxY;

	BounceType mBounceType;
};

#endif