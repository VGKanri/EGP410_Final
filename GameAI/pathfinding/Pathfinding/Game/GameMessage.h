#pragma once

#include <Trackable.h>

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	PATH_TO_MESSAGE = 1,
	EXIT_GAME_MESSAGE = 2,
	CHANGE_PATHFINDING_MESSAGE = 3,
	CHANGE_PLAYER_DIRECTION_MESSAGE = 4,
	COIN_PICK_UP_MESSAGE = 5,
	CHANGE_ROOM_MESSAGE = 6,
	CHANGE_MENU_SELECTION_MESSAGE = 7,
	CHANGE_STATE_MESSAGE = 8,
	CANDY_PICK_UP_MESSAGE = 9,
	POWER_UP_OVER_MESSAGE = 10
};

class GameMessage: public Trackable
{
public:
	friend class GameMessageManager;

	GameMessage( MessageType type  );
	~GameMessage();

	double getSubmittedTime() const { return mSubmittedTime; };
	double getScheduledTime() const { return mScheduledTime; };

protected:
	MessageType mType;
	double mSubmittedTime;
	double mScheduledTime;

private:
	virtual void process() = 0; 
};


