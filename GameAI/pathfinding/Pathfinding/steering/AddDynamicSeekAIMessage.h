#ifndef ADD_DYNAMIC_SEEK_AI
#define ADD_DYNAMIC_SEEK_AI

#include "GameMessage.h"

//adds a dynamic AI unit 200 units away from the player

class AddDynamicSeekAIMessage :public GameMessage
{
public:
	AddDynamicSeekAIMessage();
	~AddDynamicSeekAIMessage();

	void process();
};

#endif