#ifndef COLLISION_AVOIDANCE
#define COLLISION_AVOIDANCE

#include "Steering.h"
#include <map>

class KinematicUnit;

class CollisionAvoidanceSteering :public Steering
{
public:
	CollisionAvoidanceSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float avoidRadius = 75.0f);
	~CollisionAvoidanceSteering(){};

	void updateSteering();
	inline bool getDanger(){ return mInDanger; };

private:
	KinematicUnit* mpMover;
	std::map<std::string, KinematicUnit*>* mpUnitList;
	float mAvoidRadius;
	bool mInDanger;
};

#endif