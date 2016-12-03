#ifndef ADD_WANDER_AND_FLEE_AI
#define ADD_WANDER_AND_FLEE_AI

#include "GameMessage.h"

class AddWanderAndFleeAIMessage : public GameMessage
{
public:
	AddWanderAndFleeAIMessage();
	~AddWanderAndFleeAIMessage();

	void process();
};

#endif