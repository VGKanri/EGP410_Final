#include "Hitcircle.h"
#include "Hitbox.h"

#include <cmath>

#include "Game.h"

#include "StateManager.h"

#include <allegro5\allegro_primitives.h>

Hitcircle::Hitcircle():
mpShowCircles(gpGame->getStateManager()->getCollisionBoxes())
{

}

Hitcircle::Hitcircle(Vector2D position, float radius):
mpShowCircles(gpGame->getStateManager()->getCollisionBoxes())
{
	mPos = position;
	mRadius = radius;
}

//logic behind collision code comes from stack overflow user e.James
//http://stackoverflow.com/questions/401847/circle-rectangle-collision-detection-intersection
bool Hitcircle::checkCollision(Hitbox& otherBox)
{
	//get the absolute value of the distances between the circle and the box
	float distanceX = abs(mPos.getX() - otherBox.getPosition().getX());
	float distanceY = abs(mPos.getY() - otherBox.getPosition().getY());

	//checks if the circle is far enough to gurantee a lack of collision
	if (distanceX > (otherBox.getWidth() / 2 + mRadius) ||
		distanceY > (otherBox.getHeight() / 2 + mRadius))
	{
		return false;
	}

	//checks if the circle is close enough to gurantee a collision. For this logic to work
	//the if statement above has to be run first
	if (distanceX <= (otherBox.getWidth()/2) ||
		distanceY <= (otherBox.getHeight() / 2))
	{
		return true;
	}

	//this checks if the circle is intersecting with the corner of the circle.
	//calculates the distance between the the center of the circle and the corner of the box
	//and then checks if the distance is less than the circle's radius
	float cornerDistanceSq = std::pow((distanceX - otherBox.getWidth() / 2), 2) +
		std::pow((distanceY - otherBox.getHeight() / 2), 2);

	return (cornerDistanceSq <= (std::pow(mRadius, 2)));
}

void Hitcircle::update(float deltaX, float deltaY)
{
	mPos.setX(mPos.getX() + deltaX);
	mPos.setY(mPos.getY() + deltaY);
}

void Hitcircle::draw()
{
	if (*mpShowCircles == true)
	{
		al_draw_circle(mPos.getX(), mPos.getY(), mRadius, al_map_rgb(0, 255, 0), 5);
	}
}