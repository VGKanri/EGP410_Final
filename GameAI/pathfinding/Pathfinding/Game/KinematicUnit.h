#pragma once

#include "Kinematic.h"
//#include "Steering.h"
//#include "Hitcircle.h"

#include <memory>

/*KinematicUnit - a unit that is derived from the Kinematic class.  Adds behaviors and max speeds and a current Steering.

Dean Lawson
Champlain College
2011
*/

//forward declarations
class Sprite;
class GraphicsBuffer;
class CollisionAvoidanceSteering;

extern Steering gNullSteering;//global object - can point to it for a "NULL" Steering

							  //minmimum forward speed a unit has to have inorder to rotate 
							  //(keeps unit from spinning in place after stopping
const float MIN_VELOCITY_TO_TURN_SQUARED = 1.0f;

class KinematicUnit : public Kinematic
{
public:
	KinematicUnit(Sprite* pSprite, const Vector2D position, float orientation, const Vector2D& velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration = 1.0f);
	KinematicUnit();
	~KinematicUnit();

	//getters and setters
	const Vector2D& getPosition() const { return mPosition; };
	float getMaxVelocity() const { return *mMaxVelocity; };
	Vector2D getVelocity() const { return mVelocity; };
	float getMaxAcceleration() const { return mMaxAcceleration; };
	
	void setTarget(const Vector2D& target) { mTarget = target; };
	void setVelocity(const Vector2D& velocity) { mVelocity = velocity; };
	void setSprite(Sprite* sprite) { mpSprite = sprite; };
	void setPosition(Vector2D pos) { mPosition = pos; };
	void setOrientation(float orientation) { mOrientation = orientation; };
	void setRotVelocity(float rotVel) { mRotationVel = rotVel; };
	void setMaxVelocity(std::shared_ptr<float> maxVel) { mMaxVelocity = maxVel; };
	void setReactionRadius(std::shared_ptr<float> reactRad) { mReactionRadius = reactRad; };
	void setMaxRotational(std::shared_ptr<float> maxRot) { mMaxRotationalVelocity = maxRot; };
	void setMaxAcceleration(float maxAccel) { mMaxAcceleration = maxAccel; };

	//check collision
	//bool checkCollisionWithWalls();

	virtual void setNewOrientation();//face the direction you are moving

									 //draw yourself to the indicated buffer
	void draw(GraphicsBuffer* pBuffer);
	//move according to the current velocities and update velocities based on current Steering
	virtual void update(float time) =0;

	//initiate behaviors
	/*
	void seek(const Vector2D& target);
	void arrive(const Vector2D& target);
	void wander();
	void dynamicSeek(KinematicUnit* pTarget);
	void dynamicFlee(KinematicUnit* pTarget);
	void dynamicArrive(KinematicUnit* pTarget);
	void wanderAndSeek(KinematicUnit* pTarget);
	void wanderAndFlee(KinematicUnit* pTarget);
	void boid();
	*/

private:
	Sprite* mpSprite;
	Steering* mpCurrentSteering;
	CollisionAvoidanceSteering* mpCollisionAvoidance;
	Vector2D mTarget;//used only for Kinematic seek and arrive
	float mMaxAcceleration;	
	std::shared_ptr<float> mMaxVelocity;
	std::shared_ptr<float> mReactionRadius;
	std::shared_ptr<float> mMaxRotationalVelocity;
	bool mBounceVertically;//if false bounce horizontally
	//Hitcircle mHitcircle;

	void setSteering(Steering* pSteering);

};
