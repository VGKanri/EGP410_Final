#pragma once

#include "GameMessage.h"
#include "GameApp.h"
#include "Vector2D.h"

//this message is fired when the user switches pathfinding types
class ChangePathfindingMessage :public GameMessage
{
public:
	ChangePathfindingMessage(PathfindType type, Vector2D startPos, Vector2D goalPos);
	~ChangePathfindingMessage() {};

	void process();

private:
	PathfindType mType;
	Vector2D mStartPos;
	Vector2D mGoalPos;
};