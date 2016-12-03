#include "AlignmentSteering.h"

#include "KinematicUnit.h"
#include "UnitManager.h"

AlignmentSteering::AlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float alignRadius)
{
	mpMover = pMover;
	mpUnitList = unitList;
	mAlignRadius = alignRadius;
}

Steering* AlignmentSteering::getSteering()
{
	int neighborCount = 0;
	mLinear = Vector2D(0, 0);

	for (auto it : *mpUnitList)
	{
		if (it.first != "player" && it.second != mpMover)
		{
			if ((mpMover->getPosition() - it.second->getPosition()).getLength() <= mAlignRadius &&
				(mpMover->getPosition() - it.second->getPosition()).getLength() >= -mAlignRadius)
			{
				mLinear += it.second->getVelocity();
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