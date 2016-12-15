#pragma once

#include "KinematicUnit.h"
#include "Hitbox.h"
#include "AStar.h"
#include "ArriveSteering.h"

const std::string ENEMY_SHEET_PATH = "../Assets/enemySpriteSheet.png";

const int ENEMY_WIDTH = 28;
const int ENEMY_HEIGHT = 22;

class Animation;
class GraphicsBuffer;

enum class EnemyState
{
	UP,
	LEFT,
	RIGHT,
	DOWN,
	IDLE
};

class Enemy : public KinematicUnit
{
private:
	//hitcircle for collision
	Hitbox mCollider;

	CURRENT_DIRECTION mDirection;
	Path* mpPath;
	Node* mpCurrentNode;
	Node* mpGoalNode;
	Grid* mpCurrentGrid;

	Animation* mpDownAnimation;
	Animation* mpUpAnimation;
	Animation* mpSideAnimation;
	Animation* mpIdleAnimation;
	Animation* mpCurrentAnimation;

	GraphicsBuffer* mpSpriteSheet;

	EnemyState mState = EnemyState::IDLE;

	//Pathfinder for the enemy
	AStar* mpPathfinder;

	void populateAnimations();

	bool mActive; //determines whether the unit is doing more than just pathfinding
	bool mArrived; //determines whether or not the unit has made it to the center of the next tile

public:
	Enemy(Sprite* pSprite, const Vector2D position, float orientation, const Vector2D& velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration = 1.0f);
	~Enemy();

	void update(float timePassed);
	void PathFind();
	void calcCurrentNode();

	void updateState();
	void isActive(Grid* grid);

	bool checkWallCollision();
	bool checkIfGoalReached();

	inline CURRENT_DIRECTION& getCurrentDirection() { return mDirection; };
	inline void setPath(Path* path) { mpPath = path; };
	inline void setGrid(Grid* grid) { mpCurrentGrid = grid; };
	inline AStar* getPathfinder() { return mpPathfinder; };
	inline void setPathfinder(AStar* pathfinder) { mpPathfinder = pathfinder; };
	inline bool getActive() { return mActive; };
};