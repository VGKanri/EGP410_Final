#pragma once

#include "KinematicUnit.h"
#include "AStar.h"
#include "ArriveSteering.h"

class Enemy : public KinematicUnit
{
private:
	CURRENT_DIRECTION mDirection;
	Path* mpPath;
	Node* mpCurrentNode;

public:
	Enemy(Sprite* pSprite, const Vector2D position, float orientation, const Vector2D& velocity, float rotationVel, std::shared_ptr<float> maxVelocity, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcceleration = 1.0f);
	~Enemy();

	void update(float timePassed);
	void PathFind();
	void calcCurrentNode();

	inline CURRENT_DIRECTION& getCurrentDirection() { return mDirection; };
	inline void setPath(Path* path) { mpPath = path; };
};