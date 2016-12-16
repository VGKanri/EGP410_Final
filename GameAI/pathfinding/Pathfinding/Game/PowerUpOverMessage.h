#pragma once

#include "GameMessage.h"

class PowerUpOverMessage : public GameMessage
{
public:
	PowerUpOverMessage();
	~PowerUpOverMessage();

	void process();
};