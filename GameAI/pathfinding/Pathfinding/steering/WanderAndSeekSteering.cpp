#include "WanderAndSeekSteering.h"
#include "KinematicUnit.h"
#include "Game.h"

WanderAndSeekSteering::WanderAndSeekSteering(KinematicUnit* pMove, KinematicUnit* pTarget, std::shared_ptr<float> targetRadius, bool shouldFlee)
:mpMover(pMove)
, mpTarget(pTarget)
, mShouldFlee(shouldFlee)
, mTargetRadius(targetRadius)
{
	mApplyDirectly = false;
}

Steering* WanderAndSeekSteering::getSteering()
{
	Vector2D direction = mpTarget->getPosition() - mpMover->getPosition();
	float distance = direction.getLength();

	//if in target radius, perform seek or flee behavior
	if (distance < *mTargetRadius)
	{
		if (!mShouldFlee)
		{
			mLinear = mpTarget->getPosition() - mpMover->getPosition();
		}
		else
		{
			mLinear = mpMover->getPosition() - mpTarget->getPosition();
		}

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
		return this;
	}
	else //else perform wander behavior
	{
		mLinear = mpMover->getOrientationAsVector() * mpMover->getMaxVelocity();
		mAngular = mpMover->getOrientation() * (genRandomBinomial() * MAX_WANDER_AND_SEEK_ROTATION);
		return this;
	}
}