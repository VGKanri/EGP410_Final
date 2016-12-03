#ifndef COHESION_STEERING
#define COHESION_STEERING

#include "Steering.h"
#include <map>

class KinematicUnit;

//part of the overall group steering class, handles the cohesion part of the boid steering

class CohesionSteering :public Steering
{
public:
	CohesionSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float cohesionRadius = 200.0f);
	~CohesionSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	std::map<std::string, KinematicUnit*>* mpUnitList;
	float mCohesionRadius;
};

#endif