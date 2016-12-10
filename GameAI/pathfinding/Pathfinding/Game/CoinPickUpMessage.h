#pragma once

#include "GameMessage.h"

class CoinPickUpMessage :public GameMessage
{
public:
	CoinPickUpMessage(int index);
	~CoinPickUpMessage();

	void process();

private:
	int mIndex;
};