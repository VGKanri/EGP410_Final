#pragma once

#include "GameMessage.h"

//this message is fired when the game should be ended
class ExitGameMessage :public GameMessage
{
public:
	ExitGameMessage();
	~ExitGameMessage() {};

	void process();
};