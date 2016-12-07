#include "ArriveSteering.h"
#include "KinematicUnit.h"

ArriveSteering::ArriveSteering(KinematicUnit *pMover, Vector2D target, float satisfactionRadius, float timeToTarget)
	:mTarget(target), mpMover(pMover)
	,mSatisfactionRadius(satisfactionRadius)
	,mTimeToTarget(timeToTarget)
{
}

Steering* ArriveSteering::getSteering()
{
	mLinear = mTarget - mpMover->getPosition();

	//Checking if inside the satisfaction radius
	if (mLinear.getLengthSquared() < mSatisfactionRadius * mSatisfactionRadius)
	{
		mLinear = gZeroVector2D;
		mAngular = mpMover->getOrientation();
		return this;
	}

	mLinear /= mTimeToTarget;

	float maxVelocity = mpMover->getMaxVelocity();

	if (mLinear.getLengthSquared() > maxVelocity * maxVelocity)//velocity too great?
	{
		//cap the velocity
		mLinear.normalize();
		mLinear *= maxVelocity;
	}

	mAngular = Kinematic::getOrientationFromVelocity(mpMover->getOrientation(), mLinear);

	return this;
}