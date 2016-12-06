#include "Player.h"

void Player::update(float time)
{
	Vector2D tempPos = mPosition;

	//PUT IN CHECK WALL COLLISION STUFF HERE

	Kinematic::update(time);
	
	//Hitbox / Hitcircle Stuff goes here
}

