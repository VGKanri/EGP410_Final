#ifndef SEPERATION_STEERING
#define SEPERATION_STEERING

#include "Steering.h"
#include <map>

class KinematicUnit;

//part of the overall group steering class, handles the seperation section of the boid steering

class SeperationSteering :public Steering
{
public:
	SeperationSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float seperationRadius = 60.0f);
	SeperationSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	std::map<std::string, KinematicUnit*>* mpUnitList;
	float mAlignRadius;
};

#endif
