#pragma once

#include "GameMessage.h"

class CandyPickUpMessage : public GameMessage
{
public:
	CandyPickUpMessage(int index);
	~CandyPickUpMessage();

	void process();

private:
	int mIndex;
};