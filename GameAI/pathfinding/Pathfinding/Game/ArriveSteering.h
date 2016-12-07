#pragma once

#include "Steering.h"

class KinematicUnit;

class ArriveSteering : public Steering
{
private:
	Vector2D mTarget;
	float mSatisfactionRadius;
	float mTimeToTarget;

	KinematicUnit* mpMover;

public:
	ArriveSteering(KinematicUnit* pMover, Vector2D target, float satisfactionRadius = 1.0f, float timeToTarget = 0.25f);
	~ArriveSteering() {};

	void setTarget(const Vector2D& target) { mTarget = target; };
	inline Vector2D getTarget() { return mTarget; };

	virtual Steering* getSteering();
};
