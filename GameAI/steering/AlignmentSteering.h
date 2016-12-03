#ifndef ALIGNMENT_STEERING
#define ALIGNMENT_STEERING

#include "Steering.h"
#include <map>

class KinematicUnit;

//part of the overall group steering class, handles the alignment part of boid steering

class AlignmentSteering :public Steering
{
public:
	AlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, float alignRadius = 200.0f);
	~AlignmentSteering() {};

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	std::map<std::string, KinematicUnit*>* mpUnitList;
	float mAlignRadius;
};

#endif