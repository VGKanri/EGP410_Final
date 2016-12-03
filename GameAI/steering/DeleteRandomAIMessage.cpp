#include "DeleteRandomAIMessage.h"
#include "Game.h"
#include "UnitManager.h"
#include "GameMessageManager.h"
#include "ExitGameMessage.h"

DeleteRandomAIMessage::DeleteRandomAIMessage()
:GameMessage(DELETE_RANDOM_AI_MESSAGE)
{
	shouldExit = false;
}

DeleteRandomAIMessage::~DeleteRandomAIMessage()
{

}

void DeleteRandomAIMessage::process()
{
	shouldExit = gpGame->getUnitManager()->deleteRandomAIUnit();

	//if there are no AI units left, exit game
	if (shouldExit == true)
	{
		GameMessage* pMessage = new ExitGameMessage(true);
		gpGame->getMessageManager()->addMessage(pMessage, 0);
	}
}