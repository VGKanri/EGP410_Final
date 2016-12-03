#include "InputManager.h"
#include "Game.h"
#include "Vector2D.h"
#include "GraphicsSystem.h"
#include "StateManager.h"

#include "GameMessageManager.h"
#include "PlayerMoveToMessage.h"
#include "ExitGameMessage.h"
#include "AddDynamicArriveAIMessage.h"
#include "AddDynamicSeekAIMessage.h"
#include "DeleteRandomAIMessage.h"
#include "AddWanderAndFleeAIMessage.h"
#include "AddWanderAndSeekAIMessage.h"
#include "AddBoidAIMessage.h"

#include <sstream>

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	cleanUp();
}

void InputManager::init()
{
	al_install_keyboard();
	al_install_mouse();

	//init allegro input
	mpEventQueue = al_create_event_queue();
	al_register_event_source(mpEventQueue, al_get_keyboard_event_source());
	al_register_event_source(mpEventQueue, al_get_mouse_event_source());
}

void InputManager::update()
{
	//get mouse state
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);

	////checks for clicks and moves player unit to mouse location
	//if (al_mouse_button_down(&mouseState, 1))//left mouse click
	//{
	//	Vector2D pos(mouseState.x, mouseState.y);
	//	GameMessage* pMessage = new PlayerMoveToMessage(pos);
	//	gpGame->getMessageManager()->addMessage(pMessage, 0);
	//}

	//create mouse text
	std::stringstream mousePos;
	mousePos << mouseState.x << ":" << mouseState.y;

	//write text at mouse position
	al_draw_text(gpGame->getFont(), al_map_rgb(255, 255, 255), mouseState.x, mouseState.y, ALLEGRO_ALIGN_CENTRE, mousePos.str().c_str());

	gpGame->getGraphicsSystem()->swap();

	while (!al_event_queue_is_empty(mpEventQueue))
	{
		al_wait_for_event(mpEventQueue, &mEvent);

		if (mEvent.type == ALLEGRO_EVENT_KEY_DOWN) ///look for keyboard events
		{
			if (mEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
			{
				//exit main game loop
				GameMessage* pMessage = new ExitGameMessage(true);
				gpGame->getMessageManager()->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_D)
			{
				//remove random ai unit
				GameMessage* pMessage = new DeleteRandomAIMessage();
				gpGame->getMessageManager()->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_I)
			{
				//toggle state manager
				//gpGame->getStateManager()->toggleActive();
				GameMessage* pMessage = new AddBoidAIMessage();
				gpGame->getMessageManager()->addMessage(pMessage, 0);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_Z)
			{
				//toggle state manager
				gpGame->getStateManager()->toggleActive();
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_V)
			{
				gpGame->getStateManager()->setState(VELOCITY);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_R)
			{
				gpGame->getStateManager()->setState(RADIUS);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_E)
			{
				gpGame->getStateManager()->setState(ANGULAR);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_B)
			{
				gpGame->getStateManager()->setState(COLLISION_BOXES);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_C)
			{
				gpGame->getStateManager()->setState(COHESION_WEIGHT);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_S)
			{
				gpGame->getStateManager()->setState(SEPERATION_WEIGHT);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_A)
			{
				gpGame->getStateManager()->setState(ALIGNMENT_WEIGHT);
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_PAD_PLUS)
			{
				gpGame->getStateManager()->addToAnEnemyStat();
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_PAD_MINUS)
			{
				gpGame->getStateManager()->subtractFromAnEnemyStat();
			}

			if (mEvent.keyboard.keycode == ALLEGRO_KEY_S && (al_key_down(&keyboardState, ALLEGRO_KEY_LCTRL) || al_key_down(&keyboardState, ALLEGRO_KEY_RCTRL)))
			{
				gpGame->getStateManager()->saveData();
			}
		}
	}
}

void InputManager::cleanUp()
{
	al_destroy_event_queue(mpEventQueue);
}