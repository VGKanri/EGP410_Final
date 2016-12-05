#pragma once

#include "Trackable.h"
#include <allegro5\allegro.h>
#include "Vector2D.h"

const std::string FILE_NAME1 = "../Game/pathgrid.txt";
const std::string FILE_NAME2 = "../Game/pathgrid2.txt";
const std::string FILE_NAME3 = "../Game/pathgrid3.txt";
const std::string FILE_NAME4 = "../Game/pathgrid4.txt";

/* This class is going to handle all the input for the
	Editor. Since it's a small program I decided not to use
	events and handlers and figured it'd be easier to handle the
	interactions between classes in the Input Manager. Not usually recommended
	but I figured it was fine considering the scope of this project.*/

class EditorInputManager : public Trackable
{
public:
	EditorInputManager();
	~EditorInputManager();

	void init();
	void update();
	void cleanUp();

private:
	//allegro member variables needed for taking in input and reading that input from the allegro event queue
	ALLEGRO_EVENT mEvent;
	ALLEGRO_EVENT_QUEUE* mpEventQueue;
};
