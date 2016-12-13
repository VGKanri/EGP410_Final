#pragma once

#include <Trackable.h>
#include <Vector2D.h>
#include <map>

#include "KinematicUnit.h"
#include "Player.h"
#include "Enemy.h"

class Sprite;
class Grid;

//Maybe take this out?
enum BehaviourType
{
};

class UnitManager : public Trackable
{
private:
	std::map<std::string, KinematicUnit*>* mpUnitList;
	int mUnitCount;

	//Shared pointers
	std::shared_ptr<float> mPtr;
	std::shared_ptr<float> mMaxVel;

public:
	UnitManager();
	~UnitManager();

	void spawnEnemies(Grid* pGrid);
	void setEnemyActive(Grid* pGrid);

	void addUnit(Sprite* sprite, Vector2D& pos, Vector2D& vel, std::shared_ptr<float> maxVel, std::shared_ptr<float> reactionRadius
		, std::shared_ptr<float> maxRotational, float maxAccel, std::string id, bool isPlayer);
	void removeUnit(std::string id);

	KinematicUnit* getUnit(std::string id);
	inline Player* getPlayer() { return dynamic_cast<Player*>(mpUnitList->at("player")); };
	inline const int getUnitCount() { return mUnitCount; };
	inline const int getMapSize() { return mpUnitList->size(); };

	inline std::map<std::string, KinematicUnit*>* getMap() { return mpUnitList; };

	void update(float timePassed);
	void draw();
	void cleanUp();
};