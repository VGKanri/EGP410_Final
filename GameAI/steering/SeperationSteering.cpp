#include "SeperationSteering.h"

#include "KinematicUnit.h"
#include "UnitManager.h"

SeperationSteering::SeperationSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float seperationRadius)
{
	mpMover = pMover;
	mpUnitList = unitList;
	mAlignRadius = seperationRadius;
}

Steering* SeperationSteering::getSteering()
{
	int neighborCount = 0;
	mLinear = Vector2D(0, 0);

	for (auto it : *mpUnitList)
	{
		if (it.first != "player" && it.second != mpMover)
		{
			if ((mpMover->getPosition() - it.second->getPosition()).getLength() < mAlignRadius && 
				(mpMover->getPosition() - it.second->getPosition()).getLength() > -mAlignRadius)
			{
				mLinear += mpMover->getPosition() - it.second->getPosition();
				++neighborCount;
			}
		}
	}

	if (neighborCount == 0)
		return this;

	mLinear /= neighborCount;
	mLinear.normalize();
	return this;
}