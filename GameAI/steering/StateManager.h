#ifndef STATE_MANAGER
#define STATE_MANAGER

#define WHITE al_map_rgb(255,255,255)
#define MAGENTA al_map_rgb(255,0,255)

#include "Trackable.h"
#include <string>
#include <memory>

enum ManagerState
{
	VELOCITY,
	RADIUS,
	ANGULAR,
	COLLISION_BOXES,
	ALIGNMENT_WEIGHT,
	COHESION_WEIGHT,
	SEPERATION_WEIGHT
};

class StateManager : public Trackable
{
public:
	StateManager(float defaultVel = 180.0f, float defaultRad = 200.0f, float defaultAngular = 25.0f, bool defaultShowBox = false, 
				 float defaultAlignWeight = 2, float defaultSeperateWeight = 3.5, float defaultCohesionWeight = 2);
	~StateManager();

	void update();

	void addToAnEnemyStat();
	void subtractFromAnEnemyStat();
	void setState(ManagerState state);
	inline void toggleActive() { mActive = !mActive; };

	void saveData();

	inline std::shared_ptr<float> getVelocity() const { return mpEnemyVel; }; 
	inline std::shared_ptr<float> getRadius() const { return mpEnemyRadius; };
	inline std::shared_ptr<float> getAngularVelocity() const { return mpEnemyAngularVel; };
	inline std::shared_ptr<bool> getCollisionBoxes() const { return mpShowCollisionBoxes; };

	inline std::shared_ptr<float> getAlignmentWeight() const { return mpAlignmentWeight; };
	inline std::shared_ptr<float> getCohesionWeight() const { return mpCohesionWeight; };
	inline std::shared_ptr<float> getSeperationWeight() const { return mpSeperationWeight; };


private:
	ManagerState mState;

	std::shared_ptr<float> mpEnemyVel;
	std::shared_ptr<float> mpEnemyRadius;
	std::shared_ptr<float> mpEnemyAngularVel;
	std::shared_ptr<bool> mpShowCollisionBoxes;

	std::shared_ptr<float> mpAlignmentWeight;
	std::shared_ptr<float> mpCohesionWeight;
	std::shared_ptr<float> mpSeperationWeight;

	std::string mEnemyVelText;
	std::string mEnemyRadiusText;
	std::string mEnemyAngularVelText;
	std::string mCollisionDebugText;
	
	std::string mAlignmentWeightText;
	std::string mCohesionWeightText;
	std::string mSeperationWeightText;

	bool mActive;
};

#endif