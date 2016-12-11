#pragma once

#include "GameMessage.h"
#include "GameApp.h"

class ChangeStateMessage : public GameMessage
{
public:
	ChangeStateMessage(GameState state);
	~ChangeStateMessage() {};

	void process();

private:
	GameState mState;
};