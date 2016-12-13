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

	//animation variables
	mpSpriteSheet = new GraphicsBuffer(ENEMY_SHEET_PATH);

	mpDownAnimation = new Animation();
	mpUpAnimation = new Animation();
	mpSideAnimation = new Animation();
	mpIdleAnimation = new Animation();

	populateAnimations();

	mpCurrentAnimation = mpIdleAnimation;
}

Enemy::~Enemy()
{
	setSteering(NULL);

	delete mpUpAnimation;
	delete mpSideAnimation;
	delete mpIdleAnimation;
	delete mpDownAnimation;
	delete mpSpriteSheet;
}

void Enemy::update(float time)
{
	Vector2D tempPos = mPosition;

	//PUT IN CHECK WALL COLLISION STUFF HERE

	//animation update
	mpCurrentAnimation->update(time);
	mpSprite = mpCurrentAnimation->getCurrentSprite();
	
	calcCurrentNode();

	mpPath = new Path(gpGameApp->getPathfinder()->findPath(mpCurrentNode, gpGameApp->getUnitManager()->getPlayer()->getCurrentNode()));

	Node* pNextNode = mpPath->getAndRemoveNextNode();

	//UNCOMMENT THIS WHEN NEEDED
	////Here you can reset the steering's target Vector2D
	//ArriveSteering* goalSteering = dynamic_cast<ArriveSteering*>(mpCurrentSteering);
	//goalSteering->setTarget(gpGameApp->getGrid()->getULCornerOfSquare(mpPath->getAndRemoveNextNode()->getId()));

	////vital for calculating mLinear
	//Steering* tmpSteering = mpCurrentSteering->getSteering();

	////if (!tmpSteering->shouldApplyDirectly())
	////{
	//	//not stopped
	//	if (getVelocity().getLengthSquared() > MIN_VELOCITY_TO_TURN_SQUARED)
	//	{
	//		setVelocity(tmpSteering->getLinear());
	//		//setOrientation(tmpSteering->getAngular());
	//	}

	//	//since we are applying the steering directly we don't want any rotational velocity
	//	setRotationalVelocity(0.0f);
	//	tmpSteering->setAngular(0.0f);
	////}

	//Kinematic::update(time);

	//calcNewVelocities(*tmpSteering, time, *mMaxVelocity, *mMaxRotationalVelocity);

	delete mpPath;
	mpPath = NULL;
	
	//Hitbox / Hitcircle Stuff goes here

	//update enemy state
	updateState();
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