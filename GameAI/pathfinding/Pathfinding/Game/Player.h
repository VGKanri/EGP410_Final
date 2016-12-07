#pragma once

#include "KinematicUnit.h"

class Player : public KinematicUnit
{
private:
	bool mAlmightyCandy; //Boolean to determine if the player has eaten the almighty candy recently
	CURRENT_DIRECTION mDirection;

public:
	Player(Sprite* pSprite, const Vector2D position, float orientation, const Vector2D& velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration = 1.0f);

	void update(float time); //Update function for the Player

	bool getIsCandied() { return mAlmightyCandy; };
	inline CURRENT_DIRECTION& getCurrentDirection() { return mDirection; };
};