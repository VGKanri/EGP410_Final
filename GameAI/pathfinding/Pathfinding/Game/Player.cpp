#include "Player.h"
#include "Sprite.h"

Player::Player(Sprite *pSprite, const Vector2D position, float orientation, const Vector2D &velocity, float rotationVel, std::shared_ptr<float> maxVelocity
	, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration)
{
	setSprite(pSprite);
	setPosition(position);
	setOrientation(orientation);
	setVelocity(velocity);
	setRotationalVelocity(rotationVel);
	setMaxVelocity(maxVelocity);
	setReactionRadius(reactionRadius);
	setMaxRotational(maxRotational);
	setMaxAcceleration(maxAcceleration);
}

void Player::update(float time)
{
	Vector2D tempPos = mPosition;

	//PUT IN CHECK WALL COLLISION STUFF HERE

	Kinematic::update(time);


	
	//Hitbox / Hitcircle Stuff goes here
}

