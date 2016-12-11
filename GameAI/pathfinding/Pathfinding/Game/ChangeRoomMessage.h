#pragma once

#include "GameMessage.h"

/*This message handles loading and drawing a different room.*/
class ChangeRoomMessage : public GameMessage
{
public:
	ChangeRoomMessage(int index);
	~ChangeRoomMessage();

	void process();

private:
	int mIndex;
};