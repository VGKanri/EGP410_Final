#include "Enemy.h"
#include "Sprite.h"
#include "GameApp.h"
#include "UnitManager.h"
#include "GameApp.h"
#include "Game.h"
#include "GridGraph.h"
#include "Grid.h"
#include "Animation.h"
#include "GraphicsBuffer.h"
#include "GameMessage.h"
#include "PathToMessage.h"
#include "GraphicsSystem.h"

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

	mCollider = Hitbox(Vector2D(mPosition.getX() - (ENEMY_WIDTH - 16), mPosition.getY()- (ENEMY_HEIGHT - 16)), ENEMY_WIDTH, ENEMY_HEIGHT);

	//A temporary goal, you're going to have to figure out how to get the position of the node
	Steering* tmpSteering = new ArriveSteering(this, Vector2D(0,0));
	setSteeringFirst(tmpSteering);
	calcCurrentNode();

	//animation variables
	mpSpriteSheet = new GraphicsBuffer(ENEMY_SHEET_PATH);

	mpDownAnimation = new Animation();
	mpUpAnimation = new Animation();
	mpSideAnimation = new Animation();
	mpIdleAnimation = new Animation();

	populateAnimations();

	mpCurrentAnimation = mpIdleAnimation;

	mpPathfinder = new AStar(gpGameApp->getGridGraph());

	mArrived = true;
	mActive = false;
}

Enemy::~Enemy()
{
	setSteering(NULL);

	delete mpUpAnimation;
	delete mpSideAnimation;
	delete mpIdleAnimation;
	delete mpDownAnimation;
	delete mpSpriteSheet;

	delete mpPathfinder;
}

void Enemy::update(float time)
{
	Vector2D tempPos = mPosition;

	if (mActive)
	{
		//PUT IN CHECK WALL COLLISION STUFF HERE
		//animation update
		mpCurrentAnimation->update(time);
		mpSprite = mpCurrentAnimation->getCurrentSprite();

		calcCurrentNode();

		//PATHFINDING HELL
		Vector2D playerPos = gpGameApp->getUnitManager()->getPlayer()->getPosition();
		if (mArrived)
		{
			mpPath = new Path(mpPathfinder->findPath(gpGameApp->getUnitManager()->getPlayer()->getCurrentNode(), mpCurrentNode));

			mpPath->getAndRemoveNextNode();
			mpGoalNode = mpPath->getAndRemoveNextNode();

			if (mpCurrentNode->getId() != gpGameApp->getUnitManager()->getPlayer()->getCurrentNode()->getId())
				dynamic_cast<ArriveSteering*>(mpCurrentSteering)->setTarget(gpGameApp->getGrid()->getULCornerOfSquare(mpGoalNode->getId()));


			mArrived = false;
		}

		//CHECK ALL 4 CORNERS TO MATCH GRID ID
		if ((mpGoalNode != NULL) && checkIfGoalReached())
		{
			mArrived = true;
		}

		//vital for calculating mLinear
		Steering* tmpSteering = mpCurrentSteering->getSteering();

		setVelocity(tmpSteering->getLinear());

		//since we are applying the steering directly we don't want any rotational velocity
		setRotationalVelocity(0.0f);
		tmpSteering->setAngular(0.0f);

		Kinematic::update(time);

		calcNewVelocities(*tmpSteering, time, *mMaxVelocity, *mMaxRotationalVelocity);

		//Check collisions
		mCollider.update(mPosition.getX() - tempPos.getX(), mPosition.getY() - tempPos.getY());
		if (checkWallCollision())
		{
			mCollider.update(tempPos.getX() - mPosition.getX(), tempPos.getY() - mPosition.getY());
			mPosition = tempPos;
		}

		//mVelocity = Vector2D(0, 0);

		delete mpPath;
		mpPath = NULL;

#ifdef VISUALIZE_PATH
		//show pathfinder visualizer
		//mpPathfinder->drawVisualization(mpCurrentGrid, gpGameApp->getGraphicsSystem()->getBackBuffer());
#endif


	//Hitbox / Hitcircle Stuff goes here

	//update enemy state
		updateState();
	}
}

void Enemy::calcCurrentNode()
{
	mpCurrentNode = gpGameApp->getGridGraph()->getNode(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mPosition.getX() + 16, mPosition.getY() + 16));
}

void Enemy::PathFind()
{

}

void Enemy::updateState()
{
	float x = mVelocity.getX();
	float y = mVelocity.getY();

	if (std::abs(x) > std::abs(y))
	{
		if (x > 0)
			mState = EnemyState::RIGHT;
		else
			mState = EnemyState::LEFT;
	}
	else
	{
		if (y > 0)
			mState = EnemyState::DOWN;
		else
			mState = EnemyState::UP;
	}

	switch (mState)
	{
	case EnemyState::UP:
		mpCurrentAnimation = mpUpAnimation;
		mFlipH = false;
		break;
	case EnemyState::DOWN:
		mpCurrentAnimation = mpDownAnimation;
		mFlipH = false;
		break;
	case EnemyState::LEFT:
		mpCurrentAnimation = mpSideAnimation;
		mFlipH = true;
		break;
	case EnemyState::RIGHT:
		mpCurrentAnimation = mpSideAnimation;
		mFlipH = false;
		break;
	}
}

void Enemy::isActive(Grid* grid)
{
	if (mpCurrentGrid == grid)
	{
		mActive = true;
	}
	else
	{
		mActive = false;
	}
}

void Enemy::populateAnimations()
{
	//Animations for normal enemy state
	for (int i = 0; i < 7; ++i)
	{
		
		mpSideAnimation->pushSprite(new Sprite(mpSpriteSheet, i * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
	}

	for (int i = 7; i < 14; ++i)
	{
		mpUpAnimation->pushSprite(new Sprite(mpSpriteSheet, i * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
	}

	for (int i = 14; i < 21; ++i)
	{
		mpDownAnimation->pushSprite(new Sprite(mpSpriteSheet, i * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
	}

	//will have an actual idle animation soon
	mpIdleAnimation->pushSprite(new Sprite(*mpSprite));
}

bool Enemy::checkWallCollision()
{
	//check if any corner of the character is overlapping a wall
	if ((gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY())) == BLOCKING_VALUE) ||
		(gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY())) == BLOCKING_VALUE) ||
		(gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY() + mCollider.getHeight())) == BLOCKING_VALUE) ||
		(gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY() + mCollider.getHeight())) == BLOCKING_VALUE))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Enemy::checkIfGoalReached()
{
	//check if all four corners of the enemy are inside the goal node
	if (gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY()) == mpGoalNode->getId()  &&
		gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY()) == mpGoalNode->getId() &&
		gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY() + mCollider.getHeight()) == mpGoalNode->getId() &&
		gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY() + mCollider.getHeight()) == mpGoalNode->getId())
	{
		return true;
	}
	else
	{
		return false;
	}
}