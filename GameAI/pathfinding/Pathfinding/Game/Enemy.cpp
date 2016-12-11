#include "Enemy.h"
#include "Sprite.h"
#include "GameApp.h"
#include "UnitManager.h"
#include "GameApp.h"
#include "Game.h"
#include "GridGraph.h"
#include "Grid.h"
#include "GameMessage.h"
#include "PathToMessage.h"

Enemy::Enemy(Sprite *pSprite, const Vector2D position, float orientation, const Vector2D &velocity, float rotationVel, std::shared_ptr<float> maxVelocity
	, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration)
{
	setSprite(pSprite);
	setPosition(position);
	setOrientation(orientation);
	setVelocity(velocity);
	setRotationalVelocity(rotationVel);
	setMaxVelocity(maxVelocity);
	setReactionRadius(reactionRadius);
	setMaxRotational(maxRotational);
	setMaxAcceleration(maxAcceleration);
	Steering* tmpSteering = new ArriveSteering(this, mPosition);
	setSteeringFirst(tmpSteering);
	calcCurrentNode();
}

void Enemy::update(float time)
{
	Vector2D tempPos = mPosition;

	//PUT IN CHECK WALL COLLISION STUFF HERE
	
	calcCurrentNode();

	mpPath = new Path(gpGameApp->getPathfinder()->findPath(mpCurrentNode, gpGameApp->getUnitManager()->getPlayer()->getCurrentNode()));

	Node* pNextNode = mpPath->getAndRemoveNextNode();

	Steering* tmpSteering = new ArriveSteering(this, gpGameApp->getGrid()->getCenterOfSquare(pNextNode->getId()));
	//Steering* tmpSteering = new ArriveSteering(this, gpGameApp->getUnitManager()->getPlayer()->getPosition());

	setSteering(tmpSteering);

	//if (!tmpSteering->shouldApplyDirectly())
	//{
		//not stopped
		if (getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED)
		{
			setVelocity(tmpSteering->getLinear());
			setOrientation(tmpSteering->getAngular());
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity(0.0f);
		tmpSteering->setAngular(0.0f);
	//}

	Kinematic::update(time);

	calcNewVelocities(*tmpSteering, time, *mMaxVelocity, *mMaxRotationalVelocity);

	//delete tmpSteering;
	//tmpSteering = NULL;

	delete mpPath;
	mpPath = NULL;
	
	//Hitbox / Hitcircle Stuff goes here
}

void Enemy::calcCurrentNode()
{
	mpCurrentNode = gpGameApp->getGridGraph()->getNode(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mPosition.getX() + 16, mPosition.getY() + 16));
}