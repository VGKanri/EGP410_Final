#ifndef DELETE_RANDOM_AI
#define DELETE_RANDOM_AI

#include "GameMessage.h"

class DeleteRandomAIMessage :public GameMessage
{
public:
	DeleteRandomAIMessage();
	~DeleteRandomAIMessage();

	void process();

private:
	bool shouldExit;
};

#endif