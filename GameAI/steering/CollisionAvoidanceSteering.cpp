#include "CollisionAvoidanceSteering.h"

#include "KinematicUnit.h"
#include "UnitManager.h"

CollisionAvoidanceSteering::CollisionAvoidanceSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float avoidRadius)
{
	mpMover = pMover;
	mpUnitList = unitList;
	mAvoidRadius = avoidRadius;
	mInDanger = false;

	mApplyDirectly = false;
}

void CollisionAvoidanceSteering::updateSteering()
{
	KinematicUnit* closestTarget = nullptr;
	float closestDistance = mAvoidRadius + 1;

	for (auto it : *mpUnitList) //iterate through unit map
	{
		if (it.first != "player" && it.second != mpMover) 
		{
			Vector2D direction = it.second->getPosition() - mpMover->getPosition();
			if (direction.getLength() < closestDistance)
			{
				closestDistance = direction.getLength();
				closestTarget = it.second;
			}
		}
	}

	if (closestTarget == nullptr)
	{
		mInDanger = false;
		mLinear = Vector2D(0, 0);
	}
	else
	{
		mInDanger = true;
		mLinear = mpMover->getPosition() - closestTarget->getPosition();

		mLinear.normalize();
		mLinear *= mpMover->getMaxVelocity();
		mAngular = 0;
	}
}