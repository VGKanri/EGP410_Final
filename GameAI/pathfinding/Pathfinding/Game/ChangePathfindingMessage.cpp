#include "ChangePathfindingMessage.h"

#include "GameMessageManager.h"
#include "PathToMessage.h"

ChangePathfindingMessage::ChangePathfindingMessage(PathfindType type, Vector2D startPos, Vector2D goalPos)
:GameMessage(CHANGE_PATHFINDING_MESSAGE)
{
	mType = type;
	mStartPos = startPos;
	mGoalPos = goalPos;
}

void ChangePathfindingMessage::process()
{
	//changes the pathfinding type in game app to the type passed in with the message
	gpGameApp->changePathfindType(mType);

	//rerun pathfinding algorithm on switch
	GameMessage* pMessage = new PathToMessage(mStartPos, mGoalPos);
	gpGameApp->getMessageManager()->addMessage(pMessage, 0);
}