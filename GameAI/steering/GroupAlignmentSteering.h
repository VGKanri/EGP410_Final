#ifndef GROUP_ALIGNMENT_STEERING
#define GROUP_ALIGNMENT_STEERING

#include "Steering.h"
#include <memory>
#include <map>

/************************************************
					(                             
   (              )\ )                          
 ( )\ (   (  (   (()/(                       )  
 )((_))\  )\))(   /(_)) (   `  )   `  )   ( /(  
((_)_((_)((_))\  (_))   )\  /(/(   /(/(   )(_)) 
 | _ )(_) (()(_) | _ \ ((_)((_)_\ ((_)_\ ((_)_  
 | _ \| |/ _` |  |  _// _ \| '_ \)| '_ \)/ _` | 
 |___/|_|\__, |  |_|  \___/| .__/ | .__/ \__,_| 
         |___/             |_|    |_|           
***************************************************/

class KinematicUnit;

class GroupAlignmentSteering :public Steering
{
public:
	GroupAlignmentSteering(KinematicUnit* pMover, std::map<std::string, KinematicUnit*>* unitList, 
		std::shared_ptr<float> alignmentWeight, std::shared_ptr<float> seperationWeight, std::shared_ptr<float> cohesionWeight);
	~GroupAlignmentSteering();

	virtual Steering* getSteering();

private:
	KinematicUnit* mpMover;
	std::map<std::string, KinematicUnit*>* mpUnitList;
	
	Steering* mpAlignment;
	Steering* mpSeperation;
	Steering* mpCohesion;

	std::shared_ptr<float> mpAlignmentWeight;
	std::shared_ptr<float> mpSeperationWeight;
	std::shared_ptr<float> mpCohesionWeight;
};

#endif
