#include "Game.h"
#include "Kinematic.h"
#include "KinematicUnit.h"
#include "Sprite.h"
#include "GraphicsSystem.h"
#include "Steering.h"

#include "GameMessageManager.h"
#include "ArriveSteering.h"


using namespace std;

Steering gNullSteering(gZeroVector2D, 0.0f);

KinematicUnit::KinematicUnit(Sprite *pSprite, const Vector2D position, float orientation, const Vector2D &velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration)
	:Kinematic(position, orientation, velocity, rotationVel)
	, mpSprite(pSprite)
	, mpCurrentSteering(NULL)
	, mMaxVelocity(maxVelocity)
	, mReactionRadius(reactionRadius)
	, mMaxRotationalVelocity(maxRotational)
	, mMaxAcceleration(maxAcceleration)
{
}

KinematicUnit::KinematicUnit()
{
}

KinematicUnit::~KinematicUnit()
{
	//delete mpCurrentSteering;
}

void KinematicUnit::draw(GraphicsBuffer* pBuffer)
{
	if (mFlip)
	{
		mpSprite->draw(*pBuffer, mPosition.getX(), mPosition.getY(), mOrientation, 1);
	}		
	else
	{
		mpSprite->draw(*pBuffer, mPosition.getX(), mPosition.getY(), mOrientation, 0);
	}		
}

void KinematicUnit::update(float time)
{
	Vector2D tempPos = mPosition;

	Steering* steering;

	if (mpCurrentSteering != NULL)
	{
		steering = mpCurrentSteering->getSteering();
	}
	else
	{
		steering = &gNullSteering;
	}

	if (steering->shouldApplyDirectly())
	{
		//not stopped
		if (getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED)
		{
			setVelocity(steering->getLinear());
			setOrientation(steering->getAngular());
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity(0.0f);
		steering->setAngular(0.0f);
	}

	//check if colliding with wall
	/*
	if (checkCollisionWithWalls())
	{
		Vector2D newVel;

		//normal behavior for AI units
		if (mBounceVertically)
		{
			newVel = Vector2D(mVelocity.getX(), -(mVelocity.getY() * 1.5));
		}
		else
		{
			newVel = Vector2D(-(mVelocity.getX() * 1.5), mVelocity.getY());
		}

		mVelocity = newVel;
	}
	*/

	//move the unit using current velocities
	Kinematic::update(time);
	//calculate new velocities
	calcNewVelocities(*steering, time, *mMaxVelocity, *mMaxRotationalVelocity);
	//update hitbox location
	tempPos = mPosition - tempPos;
	//move to oposite side of screen if we are off
	//GRAPHICS_SYSTEM->wrapCoordinates( mPosition );

	//set the orientation to match the direction of travel
	setNewOrientation();
}

/*
bool KinematicUnit::checkCollisionWithWalls()
{
	for (int i = 0; i < gpGame->getWallManager()->getNumOfWalls(); i++)
	{
		if (mHitcircle.checkCollision(gpGame->getWallManager()->getWall(i)->getHitbox()))
		{
			if (gpGame->getWallManager()->getWall(i)->getBounceType() == VERTICAL)
			{
				mBounceVertically = true;
			}
			else
			{
				mBounceVertically = false;
			}

			return true;
		}
	}

	return false;
}
*/
//private - deletes old Steering before setting
void KinematicUnit::setSteering(Steering* pSteering)
{
	delete mpCurrentSteering;
	mpCurrentSteering = pSteering;
}

void KinematicUnit::setSteeringFirst(Steering* pSteering)
{
	mpCurrentSteering = pSteering;
}


void KinematicUnit::setNewOrientation()
{
	mOrientation = getOrientationFromVelocity(mOrientation, mVelocity);
}
/*
void KinematicUnit::seek(const Vector2D &target)
{
	KinematicSeekSteering* pSeekSteering = new KinematicSeekSteering(this, target);
	setSteering(pSeekSteering);
}

void KinematicUnit::arrive(const Vector2D &target)
{
	KinematicArriveSteering* pArriveSteering = new KinematicArriveSteering(this, target);
	setSteering(pArriveSteering);
}

void KinematicUnit::wander()
{
	KinematicWanderSteering* pWanderSteering = new KinematicWanderSteering(this);
	setSteering(pWanderSteering);
}

void KinematicUnit::dynamicSeek(KinematicUnit* pTarget)
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering(this, pTarget);
	setSteering(pDynamicSeekSteering);
}

void KinematicUnit::dynamicFlee(KinematicUnit* pTarget)
{
	DynamicSeekSteering* pDynamicSeekSteering = new DynamicSeekSteering(this, pTarget, true);
	setSteering(pDynamicSeekSteering);
}

void KinematicUnit::dynamicArrive(KinematicUnit* pTarget)
{
	DynamicArriveSteering* pDynamicArriveSteering = new DynamicArriveSteering(this, pTarget);
	setSteering(pDynamicArriveSteering);
}

void KinematicUnit::wanderAndSeek(KinematicUnit* pTarget)
{
	WanderAndSeekSteering* pWanderAndSeekSteering = new WanderAndSeekSteering(this, pTarget, mReactionRadius);
	setSteering(pWanderAndSeekSteering);
}

void KinematicUnit::wanderAndFlee(KinematicUnit* pTarget)
{
	WanderAndSeekSteering* pWanderAndSeekSteering = new WanderAndSeekSteering(this, pTarget, mReactionRadius, true);
	setSteering(pWanderAndSeekSteering);
}

void KinematicUnit::boid()
{
	GroupAlignmentSteering* pBoidSteering = new GroupAlignmentSteering(this, gpGame->getUnitManager()->getMap(), gpGame->getStateManager()->getAlignmentWeight(),
		gpGame->getStateManager()->getSeperationWeight(), gpGame->getStateManager()->getCohesionWeight());

	setSteering(pBoidSteering);
}
*/