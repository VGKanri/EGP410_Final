#ifndef EXIT_GAME_M
#define EXIT_GAME_M

#include "GameMessage.h"

class ExitGameMessage :public GameMessage
{
public:
	ExitGameMessage(bool shouldExit);
	~ExitGameMessage();

	void process();

private:
	bool mShouldExit;
};

#endif