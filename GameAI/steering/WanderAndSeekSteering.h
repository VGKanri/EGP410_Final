#ifndef WANDER_AND_SEEK_BEHAVIOR
#define WANDER_AND_SEEK_BEHAVIOR

#include "Steering.h"
#include <memory>

class KinematicUnit;

const float MAX_WANDER_AND_SEEK_ROTATION = 120.0f;

class WanderAndSeekSteering :public Steering
{
public:
	WanderAndSeekSteering(KinematicUnit* pMove, KinematicUnit* pTarget, std::shared_ptr<float> targetRadius, bool shouldFlee = false);
	~WanderAndSeekSteering(){};

	void setTarget(KinematicUnit* pTarget){ mpTarget = pTarget; };

	virtual Steering* getSteering();

private:
	KinematicUnit* mpTarget;
	KinematicUnit* mpMover;
	//float mTargetRadius;
	std::shared_ptr<float> mTargetRadius;
	bool mShouldFlee;
};

#endif