#ifndef ADD_DYNAMIC_ARRIVE_AI
#define ADD_DYNAMIC_ARRIVE_AI

#include "GameMessage.h"

//adds a dynamic AI unit 200 units away from the player

class AddDynamicArriveAIMessage :public GameMessage
{
public:
	AddDynamicArriveAIMessage();
	~AddDynamicArriveAIMessage();

	void process();
};

#endif