#ifndef ADD_BOID_AI
#define ADD_BOID_AI

#include "GameMessage.h"

//this message will add 5 boids to the middle of the screen

class AddBoidAIMessage :public GameMessage
{
public:
	AddBoidAIMessage();
	~AddBoidAIMessage();

	void process();
};

#endif