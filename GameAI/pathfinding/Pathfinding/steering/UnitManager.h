#ifndef UNIT_MANAGER
#define UNIT_MANAGER

#include <Trackable.h>
#include <Vector2D.h>
#include <map>

#include "KinematicUnit.h"

class Sprite;

enum BehaviorType
{
	DYNAMIC_ARRIVE,
	DYNAMIC_SEEK,
	WANDER_AND_SEEK,
	WANDER_AND_FLEE,
	BOID
};

class UnitManager :public Trackable
{
public:
	UnitManager();
	~UnitManager();

	void addUnit(Sprite* sprite, Vector2D& pos, Vector2D& vel, std::shared_ptr<float> maxVel, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational,float maxAcc, std::string id, bool isPlayer = false);
	void removeUnit(std::string id);
	void setUnitBehavior(BehaviorType type, std::string entityID, std::string targetID);
	KinematicUnit* getUnit(std::string id);
	bool deleteRandomAIUnit();
	inline const int getUnitCount(){ return mUnitCount; };
	inline const int getMapSize(){ return mpUnitList->size(); };
	inline std::map<std::string, KinematicUnit*>* getMap(){ return mpUnitList; };

	void update(double timePassed);
	void draw();
	void cleanUp();

private:
	std::map<std::string, KinematicUnit*>* mpUnitList;

	int mUnitCount;
};

#endif