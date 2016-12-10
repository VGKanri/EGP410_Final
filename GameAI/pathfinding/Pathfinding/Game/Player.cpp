#include "Player.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsBuffer.h"
#include "Hitcircle.h"
#include "Grid.h"
#include "Game.h"
#include "GameApp.h"

Player::Player(Sprite *pSprite, const Vector2D position, float orientation, const Vector2D &velocity, float rotationVel, std::shared_ptr<float> maxVelocity
	, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration)
{
	setSprite(pSprite);
	setPosition(Vector2D(position.getX() - 16, position.getY() - 16));
	setOrientation(orientation);
	setVelocity(velocity);
	setRotationalVelocity(rotationVel);
	setMaxVelocity(maxVelocity);
	setReactionRadius(reactionRadius);
	setMaxRotational(maxRotational);
	setMaxAcceleration(maxAcceleration);

	mCollider = Hitbox(Vector2D(mPosition.getX() - (PLAYER_WIDTH - 16), mPosition.getY() - (PLAYER_HEIGHT - 16)), PLAYER_WIDTH, PLAYER_HEIGHT);

	mpSpriteSheet = new GraphicsBuffer(PLAYER_SHEET_PATH);

	mpDownAnimation = new Animation();
	mpUpAnimation = new Animation();
	mpSideAnimation = new Animation();
	mpIdleAnimation = new Animation();

	populateAnimations();

	mpCurrentAnimation = mpIdleAnimation;
}

Player::~Player()
{
	delete mpUpAnimation;
	delete mpSideAnimation;
	delete mpIdleAnimation;
	delete mpDownAnimation;
	delete mpSpriteSheet;
}

void Player::update(float time)
{
	Vector2D tempPos = mPosition;

	//ANIMATION UPDATE
	mpCurrentAnimation->update(time);
	mpSprite = mpCurrentAnimation->getCurrentSprite();

	//PUT IN CHECK WALL COLLISION STUFF HERE
	Kinematic::update(time);

	//Hitbox / Hitcircle Stuff goes here
	mCollider.update(mPosition.getX() - tempPos.getX(), mPosition.getY() - tempPos.getY());
	if (checkWallCollision())
	{
		mCollider.update(tempPos.getX() - mPosition.getX(), tempPos.getY() - mPosition.getY());
		mPosition = tempPos;
		changeState(PlayerState::IDLE);
	}
}

void Player::changeState(PlayerState newState)
{
	mState = newState;

	switch (mState)
	{
	case PlayerState::UP:
		mpCurrentAnimation = mpUpAnimation;
		break;
	case PlayerState::LEFT:
		mpCurrentAnimation = mpSideAnimation;
		mFlip = true;
		break;
	case PlayerState::RIGHT:
		mpCurrentAnimation = mpSideAnimation;
		mFlip = false;
		break;
	case PlayerState::DOWN:
		mpCurrentAnimation = mpDownAnimation;
		break;
	case PlayerState::IDLE:
		mpCurrentAnimation = mpIdleAnimation;
		break;
	}
}

void Player::populateAnimations()
{
	for (int i = 0; i < 10; ++i)
	{
		mpUpAnimation->pushSprite(new Sprite(mpSpriteSheet, i * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
	}

	for (int i = 0; i < 10; ++i)
	{
		mpSideAnimation->pushSprite(new Sprite(mpSpriteSheet, i * SPRITE_SIZE, 32, SPRITE_SIZE, SPRITE_SIZE));
	}

	for (int i = 0; i < 10; ++i)
	{
		mpDownAnimation->pushSprite(new Sprite(mpSpriteSheet, i * SPRITE_SIZE, 64, SPRITE_SIZE, SPRITE_SIZE));
	}

	//will have an actual idle animation soon
	mpIdleAnimation->pushSprite(new Sprite(*mpSprite));
}

bool Player::checkWallCollision()
{
	//+ mCollider.getWidth()
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