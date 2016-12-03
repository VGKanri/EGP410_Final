#ifndef GAME_MESSAGE
#define GAME_MESSAGE

#include "Trackable.h"

enum MessageType
{
	INVALID_MESSAGE_TYPE = -1,
	PLAYER_MOVETO_MESSAGE = 0,
	EXIT_GAME_MESSAGE = 1,
	ADD_DYNAMIC_ARRIVE_AI_MESSAGE = 2,
	ADD_DYNAMIC_SEEK_AI_MESSAGE = 3,
	DELETE_RANDOM_AI_MESSAGE = 4,
	ADD_WANDER_AND_SEEK_AI_MESSAGE = 5,
	ADD_WANDER_AND_FLEE_AI_MESSAGE = 6,
	ADD_BOID_MESSAGE = 7
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

#endif