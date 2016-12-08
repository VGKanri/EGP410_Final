#include "Player.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsBuffer.h"

Player::Player(Sprite *pSprite, const Vector2D position, float orientation, const Vector2D &velocity, float rotationVel, std::shared_ptr<float> maxVelocity
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
}

void Player::changeState(PlayerState newState)
{
	mState = newState;

	switch (mState)
	{
	case up:
		mpCurrentAnimation = mpUpAnimation;
		break;
	case left_:
		mpCurrentAnimation = mpSideAnimation;
		mFlip = true;
		break;
	case right_:
		mpCurrentAnimation = mpSideAnimation;
		mFlip = false;
		break;
	case down:
		mpCurrentAnimation = mpDownAnimation;
		break;
	case idle:
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

