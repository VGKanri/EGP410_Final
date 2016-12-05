#include "ChangePlayerDirectionMessage.h"
#include "GameApp.h"
#include "UnitManager.h"

ChangePlayerDirectionMessage::ChangePlayerDirectionMessage(int direction)
:GameMessage(CHANGE_PLAYER_DIRECTION_MESSAGE)
,mDirection(direction)
{
}

ChangePlayerDirectionMessage::~ChangePlayerDirectionMessage()
{
}

void ChangePlayerDirectionMessage::process()
{
	//Add in get UnitManager Here and process direction change
	std::cout << "My direction is: " << mDirection << std::endl;
}