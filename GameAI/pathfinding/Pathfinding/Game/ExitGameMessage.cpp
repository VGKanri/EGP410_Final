#include "ExitGameMessage.h"
#include "Game.h"

ExitGameMessage::ExitGameMessage()
:GameMessage(EXIT_GAME_MESSAGE)
{

}

void ExitGameMessage::process()
{
	//sets the mExit bool in GameApp to true
	gpGame->markForExit();
}