#include "Player.h"
#include "Enemy.h"
#include "UnitManager.h"
#include "Sprite.h"
#include "Animation.h"
#include "GraphicsBuffer.h"
#include "Hitcircle.h"
#include "Grid.h"
#include "Game.h"
#include "GameApp.h"
#include "SoundManager.h"
#include "GridPathfinder.h"
#include "GridGraph.h"
#include "CoinPickUpMessage.h"
#include "CandyPickUpMessage.h"
#include "ChangeRoomMessage.h"
#include "PowerUpOverMessage.h"
#include "SpawnEnemyMessage.h"
#include "GameMessageManager.h"

Player::Player(Sprite *pSprite, const Vector2D position, float orientation, const Vector2D &velocity, float rotationVel, std::shared_ptr<float> maxVelocity
	, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration)
{
	setSprite(pSprite);
	setPosition(Vector2D(position.getX(), position.getY()));
	setOrientation(orientation);
	setVelocity(velocity);
	setRotationalVelocity(rotationVel);
	setMaxVelocity(maxVelocity);
	setReactionRadius(reactionRadius);
	setMaxRotational(maxRotational);
	setMaxAcceleration(maxAcceleration);

	mCollider = Hitbox(Vector2D(mPosition.getX() - (PLAYER_WIDTH - 16), mPosition.getY() - (PLAYER_HEIGHT - 16)), PLAYER_WIDTH, PLAYER_HEIGHT);

	mCandyTimer = 0;

	mAlmightyCandy = false;
	mInDoor = false;

	mpSpriteSheet = new GraphicsBuffer(PLAYER_SHEET_PATH);
	mpPowerSheet = new GraphicsBuffer(POWER_SHEET_PATH);

	mpDownAnimation = new Animation();
	mpUpAnimation = new Animation();
	mpSideAnimation = new Animation();
	mpIdleAnimation = new Animation();

	mpSidePAnimation = new Animation();
	mpUpPAnimation = new Animation();
	mpDownPAnimation = new Animation();

	populateAnimations();

	mpCurrentAnimation = mpIdleAnimation;

	calcCurrentNode();
}

Player::~Player()
{
	delete mpUpAnimation;
	delete mpSideAnimation;
	delete mpIdleAnimation;
	delete mpDownAnimation;
	delete mpSpriteSheet;

	delete mpUpPAnimation;
	delete mpDownPAnimation;
	delete mpSidePAnimation;
	delete mpPowerSheet;
}

void Player::update(float time)
{
	calcCurrentNode();

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

	checkCoinCollision();
	checkCandyCollision();
	checkEnemyCollision();

	//handle door logic
	int result = checkDoorCollision();
	if (result != -1 && !mInDoor)
	{
		mInDoor = true;
		GameMessage* pMessage = new ChangeRoomMessage(result);
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
		
	}
	else if (result == -1)
	{
		mInDoor = false;
	}

	//handle candy timer logic
	updateCandyTimer(time);
}

void Player::updateCandyTimer(float time)
{
	mCandyTimer += time;

	if (mCandyTimer >= CANDY_LIMIT)
	{
		mCandyTimer = 0;
		mAlmightyCandy = false;

		//I'm sorry, but it has to be done
		gpGameApp->getSoundManager()->stopSong();
		gpGameApp->getSoundManager()->playSong(BATTLE_THEME_KEY);
	}
}

void Player::changeState(PlayerState newState)
{
	mState = newState;

	switch (mState)
	{
	case PlayerState::UP:
		if (mAlmightyCandy)
			mpCurrentAnimation = mpUpPAnimation;
		else
			mpCurrentAnimation = mpUpAnimation;

		mFlipH = false;
		break;
	case PlayerState::LEFT:
		if (mAlmightyCandy)
			mpCurrentAnimation = mpSidePAnimation;
		else
			mpCurrentAnimation = mpSideAnimation;

		mFlipH = true;
		break;
	case PlayerState::RIGHT:
		if (mAlmightyCandy)
			mpCurrentAnimation = mpSidePAnimation;
		else
			mpCurrentAnimation = mpSideAnimation;

		mFlipH = false;
		break;
	case PlayerState::DOWN:
		if (mAlmightyCandy)
			mpCurrentAnimation = mpDownPAnimation;
		else
			mpCurrentAnimation = mpDownAnimation;

		mFlipH = false;
		break;
	case PlayerState::IDLE:
		mpCurrentAnimation = mpIdleAnimation;

		mFlipH = false;
		break;
	}
}

void Player::resetCollider()
{
	mCollider = Hitbox(Vector2D(mPosition.getX() - (PLAYER_WIDTH - 16), mPosition.getY() - (PLAYER_HEIGHT - 16)), PLAYER_WIDTH, PLAYER_HEIGHT);
}

void Player::populateAnimations()
{
	//Animations for normal player state
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

	//animations for powered up state
	for (int i = 0; i < 10; ++i)
	{
		mpSidePAnimation->pushSprite(new Sprite(mpPowerSheet, i * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
	}

	for (int i = 10; i < 20; ++i)
	{
		mpDownPAnimation->pushSprite(new Sprite(mpPowerSheet, i * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
	}

	for (int i = 20; i < 30; ++i)
	{
		mpUpPAnimation->pushSprite(new Sprite(mpPowerSheet, i * SPRITE_SIZE, 0, SPRITE_SIZE, SPRITE_SIZE));
	}
}

bool Player::checkWallCollision()
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

void Player::checkCoinCollision()
{
	//check if any corner of the character is overlapping a coin
	if (gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY())) == COIN)
	{
		GameMessage* pMessage = new CoinPickUpMessage(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY()));
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY())) == COIN)
	{
		GameMessage* pMessage = new CoinPickUpMessage(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY()));
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY() + mCollider.getHeight())) == COIN)
	{
		GameMessage* pMessage = new CoinPickUpMessage(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY() + mCollider.getHeight()));
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY() + mCollider.getHeight())) == COIN)
	{
		GameMessage* pMessage = new CoinPickUpMessage(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY() + mCollider.getHeight()));
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
}

void Player::checkCandyCollision()
{
	//check if any corner of the character is overlapping a coin
	if (gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY())) == CANDY_SPAWN)
	{
		GameMessage* pMessage = new CandyPickUpMessage(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY()));
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY())) == CANDY_SPAWN)
	{
		GameMessage* pMessage = new CandyPickUpMessage(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY()));
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY() + mCollider.getHeight())) == CANDY_SPAWN)
	{
		GameMessage* pMessage = new CandyPickUpMessage(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY() + mCollider.getHeight()));
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
	else if (gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY() + mCollider.getHeight())) == CANDY_SPAWN)
	{
		GameMessage* pMessage = new CandyPickUpMessage(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY() + mCollider.getHeight()));
		gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	}
}

int Player::checkDoorCollision()
{
	int corner1 = gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY()));
	int corner2 = gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY()));
	int corner3 = gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY() + mCollider.getHeight()));
	int corner4 = gpGameApp->getGrid()->getValueAtIndex(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY() + mCollider.getHeight()));

	//check if any corner of the character is overlapping a door tile
	if (corner1 >= DOOR_1 && corner1 <= DOOR_4)
	{
		return gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY());
	}
	else if (corner2 >= DOOR_1 && corner2 <= DOOR_4)
	{
		return gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY());
	}
	else if (corner3 >= DOOR_1 && corner3 <= DOOR_4)
	{
		return gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX(), mCollider.getPosition().getY() + mCollider.getHeight());
	}
	else if (corner4 >= DOOR_1 && corner4 <= DOOR_4)
	{
		return gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + mCollider.getWidth(), mCollider.getPosition().getY() + mCollider.getHeight());
	}
	else
	{
		return -1; //signifies no door collision is occuring
	}
}

void Player::checkEnemyCollision()
{
	std::vector<Enemy*> enemyList = gpGameApp->getUnitManager()->getEnemyList();

	for (Enemy* enemy : enemyList)
	{
		if (mCollider.checkCollision(enemy->getCollider()))
		{
			if (mAlmightyCandy)
			{
				//kill enemies
				enemy->setDead(true);

				GameMessage* pMessage = new SpawnEnemyMessage(enemy);
				gpGameApp->getMessageManager()->addMessage(pMessage, 10000);
			}
			else
			{
				//kill player
			}
		}
	}
}

//Getting the node that the player is currently in
void Player::calcCurrentNode()
{
	mpCurrentNode = gpGameApp->getGridGraph()->getNode(gpGameApp->getGrid()->getSquareIndexFromPixelXY(mCollider.getPosition().getX() + 16, mCollider.getPosition().getY()));
}