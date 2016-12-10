#pragma once

#include "KinematicUnit.h"
#include "Hitbox.h"
#include <string>

const std::string PLAYER_SHEET_PATH = "../Assets/rocketSpriteSheet.png";
const int SPRITE_SIZE = 32;
const float PLAYER_SPEED = 120;

class Animation;
class GraphicsBuffer;
class Grid;

enum class PlayerState
{
	UP,
	LEFT,
	RIGHT,
	DOWN,
	IDLE
};

const int PLAYER_WIDTH = 22;
const int PLAYER_HEIGHT = 20;

class Player : public KinematicUnit
{
private:
	//hitcircle for collision
	Hitbox mCollider;

	//will probably clean this up later to be an array
	Animation* mpDownAnimation;
	Animation* mpUpAnimation;
	Animation* mpSideAnimation;
	Animation* mpIdleAnimation;
	Animation* mpCurrentAnimation;

	GraphicsBuffer* mpSpriteSheet;

	PlayerState mState = PlayerState::IDLE;

	bool mAlmightyCandy; //Boolean to determine if the player has eaten the almighty candy recently
	CURRENT_DIRECTION mDirection;

	void populateAnimations();

public:
	Player(Sprite* pSprite, const Vector2D position, float orientation, const Vector2D& velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration = 1.0f);
	~Player();

	void update(float time); //Update function for the Player

	void changeState(PlayerState newState);

	bool checkWallCollision();
	void checkCoinCollision();

	inline Hitbox getHitbox() const { return mCollider; };
	bool getIsCandied() { return mAlmightyCandy; };
	inline CURRENT_DIRECTION& getCurrentDirection() { return mDirection; };
};