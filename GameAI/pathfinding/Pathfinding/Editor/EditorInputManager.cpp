#include "EditorInputManager.h"
#include "Grid.h"
#include "GridVisualizer.h"

#include "Editor.h"
#include "Game.h"

#include <fstream>
#include <iostream>

EditorInputManager::EditorInputManager()
{
}

EditorInputManager::~EditorInputManager()
{
	cleanUp();
}

void EditorInputManager::init()
{
	al_install_keyboard();
	al_install_mouse();

	//init allegro input
	mpEventQueue = al_create_event_queue();
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());
}

void EditorInputManager::update()
{
	//gpGame so we can access editor specfic properties
	Editor* pEditor = dynamic_cast<Editor*>(gpGame);

	//get input states
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);

	if (al_mouse_button_down(&mouseState, 1))//left mouse click
	{
		pEditor->getGrid()->setValueAtPixelXY(mouseState.x, mouseState.y, BLOCKING_VALUE);
		pEditor->getGridVisualizer()->setModified();
	}

	if (al_mouse_button_down(&mouseState, 2))//right mouse click
	{
		pEditor->getGrid()->setValueAtPixelXY(mouseState.x, mouseState.y, CLEAR_VALUE);
		pEditor->getGridVisualizer()->setModified();
	}

	while (!al_event_queue_is_empty(mpEventQueue))
	{
		al_wait_for_event(mpEventQueue, &mEvent);

		if (mEvent.type == ALLEGRO_EVENT_KEY_DOWN) ///look for keyboard events
		{
			//if escape key was down then exit the loop
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				gpGame->markForExit();
			}
			else if (mEvent.keyboard.keycode == ALLEGRO_KEY_S)
			{
				Editor* pEditor = dynamic_cast<Editor*>(gpGame);
				if (pEditor != NULL)
				{
					std::ofstream theStream(FILE_NAME1);
					pEditor->saveGrid(theStream);
					theStream.close();
					std::cout << "Grid saved!\n";
					Sleep(1000);//very bogus
				}
			}
			else if (mEvent.keyboard.keycode == ALLEGRO_KEY_L)
			{
				Editor* pEditor = dynamic_cast<Editor*>(gpGame);
				if (pEditor != NULL)
				{
					std::ifstream theStream(FILE_NAME1);
					pEditor->loadGrid(theStream);
					theStream.close();
					pEditor->getGridVisualizer()->setModified();
					std::cout << "Grid loaded!\n";
					Sleep(1000);//very bogus
				}
			}
		}
	}
}

void EditorInputManager::cleanUp()
{
	al_destroy_event_queue(mpEventQueue);
}