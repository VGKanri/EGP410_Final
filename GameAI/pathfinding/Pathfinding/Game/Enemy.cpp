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

	//A temporary goal, you're going to have to figure out how to get the positoin of the node
	Steering* tmpSteering = new ArriveSteering(this, Vector2D(500,500));
	setSteeringFirst(tmpSteering);
	calcCurrentNode();
}

Enemy::~Enemy()
{
	setSteering(NULL);
}

void Enemy::update(float time)
{
	Vector2D tempPos = mPosition;

	//PUT IN CHECK WALL COLLISION STUFF HERE
	
	calcCurrentNode();

	mpPath = new Path(gpGameApp->getPathfinder()->findPath(mpCurrentNode, gpGameApp->getUnitManager()->getPlayer()->getCurrentNode()));

	Node* pNextNode = mpPath->getAndRemoveNextNode();

	//Here you can reset the steering's target Vector2D
	ArriveSteering* goalSteering = dynamic_cast<ArriveSteering*>(mpCurrentSteering);
	goalSteering->setTarget(gpGameApp->getGrid()->getULCornerOfSquare(mpPath->getAndRemoveNextNode()->getId()));

	//vital for calculating mLinear
	Steering* tmpSteering = mpCurrentSteering->getSteering();

	//if (!tmpSteering->shouldApplyDirectly())
	//{
		//not stopped
		if (getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED)
		{
			setVelocity(tmpSteering->getLinear());
			//setOrientation(tmpSteering->getAngular());
		}

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity(0.0f);
		tmpSteering->setAngular(0.0f);
	//}

	Kinematic::update(time);

	calcNewVelocities(*tmpSteering, time, *mMaxVelocity, *mMaxRotationalVelocity);

	delete mpPath;
	mpPath = NULL;
	
	//Hitbox / Hitcircle Stuff goes here
}

void Enemy::calcCurrentNode()
{
	mpCurrentNode = gpGameApp->getGridGraph()->getNode(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mPosition.getX() + 16, mPosition.getY() + 16));
}

void Enemy::PathFind()
{

}