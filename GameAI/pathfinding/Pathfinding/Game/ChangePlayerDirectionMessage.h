#pragma once

#include "GameMessage.h"
#include "GameApp.h"
#include "Vector2D.h"

class ChangePlayerDirectionMessage : public GameMessage
{
public:
	ChangePlayerDirectionMessage(int direction);
	~ChangePlayerDirectionMessage();

	void process();
private:
	int mDirection;
};