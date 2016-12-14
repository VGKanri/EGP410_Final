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
	mLinear = mTarget - Vector2D(mpMover->getPosition().getX(), mpMover->getPosition().getY());

	mLinear.normalize();
	mLinear *= mpMover->getMaxVelocity();
	mAngular = 0;

	return this;
}