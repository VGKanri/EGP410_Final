#include "Hitbox.h"

#include "Vector2D.h"

#include "Game.h"

#include <allegro5\allegro_primitives.h>

Hitbox::Hitbox()
{

}


Hitbox::Hitbox(Vector2D position, float width, float height)
{
	minX = position.getX();
	minY = position.getY();
	maxX = minX + width;
	maxY = minY + height;
}

Hitbox::Hitbox(float x1, float y1, float x2, float y2)
{
	minX = x1;
	minY = y1;
	maxX = x2;
	maxY = y2;
}


Hitbox::~Hitbox()
{

}

bool Hitbox::checkCollision(Hitbox& otherBox)
{
	if (minX < otherBox.maxX && maxX > otherBox.minX &&
		minY < otherBox.maxY && maxY > otherBox.minY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Hitbox::draw()
{
	/*if (*mpShowBoxes == true)
	{
		al_draw_rectangle(minX, minY, maxX, maxY, al_map_rgb(0, 255, 0), 3.0f);
	}	*/
}

void Hitbox::update(float deltaX, float deltaY)
{
	minX += deltaX;
	maxX += deltaX;
	minY += deltaY;
	maxY += deltaY;
}

Vector2D Hitbox::getPosition()
{
	return Vector2D(minX + ((maxX - minX) / 2), minY + ((maxY - minY) / 2));
}