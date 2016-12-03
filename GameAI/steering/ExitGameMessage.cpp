#include "ExitGameMessage.h"
#include "GameMessageManager.h"
#include "Game.h"

ExitGameMessage::ExitGameMessage(bool shouldExit)
:GameMessage(EXIT_GAME_MESSAGE)
{
	mShouldExit = shouldExit;
}

ExitGameMessage::~ExitGameMessage()
{

}

void ExitGameMessage::process()
{
	gpGame->setShouldExit(mShouldExit);
}