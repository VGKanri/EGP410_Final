#ifndef ADD_WANDER_AND_SEEK_AI
#define ADD_WANDER_AND_SEEK_AI

#include "GameMessage.h"

class AddWanderAndSeekAIMessage : public GameMessage
{
public:
	AddWanderAndSeekAIMessage();
	~AddWanderAndSeekAIMessage();

	void process();
};

#endif