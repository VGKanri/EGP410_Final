#ifndef INPUT_MANAGER
#define INPUT_MANAGER

#include "Trackable.h"
#include <allegro5\allegro.h>
#include "Vector2D.h"

class InputManager : public Trackable
{
public:
	InputManager();
	~InputManager();

	void init();
	void update();
	void cleanUp();

private:
	//allegro member variables needed for taking in input and reading that input from the allegro event queue
	ALLEGRO_EVENT mEvent;
	ALLEGRO_EVENT_QUEUE* mpEventQueue;

	Vector2D mStartPos;
	Vector2D mGoalPos;
};

#endif