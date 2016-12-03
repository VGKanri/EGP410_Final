#ifndef KINEMATIC_UNIT
#define KINEMATIC_UNIT

#include "Kinematic.h"
#include "Steering.h"
#include "Hitcircle.h"

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

class KinematicUnit: public Kinematic
{
public:
	KinematicUnit( Sprite* pSprite, const Vector2D& position, float orientation, const Vector2D& velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration = 1.0f, bool isPlayer = false );
	~KinematicUnit();

	//getters and setters
	void setTarget( const Vector2D& target ) { mTarget = target; };
	const Vector2D& getPosition() const { return mPosition; };
	float getMaxVelocity() const { return *mMaxVelocity; };
	Vector2D getVelocity() const { return mVelocity; };
	float getMaxAcceleration() const { return mMaxAcceleration; };
	void setVelocity( const Vector2D& velocity ){ mVelocity = velocity; };

	//check collision
	bool checkCollisionWithWalls();

	virtual void setNewOrientation();//face the direction you are moving

	//draw yourself to the indicated buffer
	void draw( GraphicsBuffer* pBuffer );
	//move according to the current velocities and update velocities based on current Steering
	void update(float time);

	//initiate behaviors
	void seek( const Vector2D& target );
	void arrive( const Vector2D& target );
	void wander();
	void dynamicSeek( KinematicUnit* pTarget );
	void dynamicFlee( KinematicUnit* pTarget );
	void dynamicArrive( KinematicUnit* pTarget );
	void wanderAndSeek(KinematicUnit* pTarget);
	void wanderAndFlee(KinematicUnit* pTarget);
	void boid();

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
	Hitcircle mHitcircle;

	bool mPlayer; //am I a player?

	void setSteering( Steering* pSteering );

};

#endif