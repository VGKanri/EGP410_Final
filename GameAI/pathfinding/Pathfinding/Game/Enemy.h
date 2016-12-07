#pragma once

#include "KinematicUnit.h"

class Enemy : public KinematicUnit
{
private:
	CURRENT_DIRECTION mDirection;
public:
	Enemy(Sprite* pSprite, const Vector2D position, float orientation, const Vector2D& velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration = 1.0f);

	void update(float timePassed);

	inline CURRENT_DIRECTION& getCurrentDirection() { return mDirection; };
};