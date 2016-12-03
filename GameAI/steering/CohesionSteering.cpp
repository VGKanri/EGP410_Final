#include "CohesionSteering.h"

#include "KinematicUnit.h"
#include "UnitManager.h"

CohesionSteering::CohesionSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float cohesionRadius)
{
	mpMover = pMover;
	mpUnitList = unitList;
	mCohesionRadius = cohesionRadius;
}

Steering* CohesionSteering::getSteering()
{
	int neighborCount = 0;
	mLinear = Vector2D(0, 0);

	for (auto it : *mpUnitList)
	{
		if (it.first != "player" && it.second != mpMover)
		{
			if ((mpMover->getPosition() - it.second->getPosition()).getLength() < mCohesionRadius && 
				(mpMover->getPosition() - it.second->getPosition()).getLength() > -mCohesionRadius)
			{
				mLinear += it.second->getPosition();
				++neighborCount;
			}
		}
	}

	if (neighborCount == 0)
		return this;

	mLinear /= neighborCount;
	mLinear = mLinear - mpMover->getPosition();
	mLinear.normalize();
	return this;
}