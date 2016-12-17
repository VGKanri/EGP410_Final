#include "InputManager.h"
#include "GameApp.h"
#include "GameMessageManager.h"

#include "ExitGameMessage.h"
#include "PathToMessage.h"
#include "ChangePlayerDirectionMessage.h"
#include "ChangeMenuSelectionMessage.h"
#include "ChangeStateMessage.h"
#include "MainMenu.h"

InputManager::InputManager()
{
	mStartPos = Vector2D(0, 0);
	mGoalPos = Vector2D(0, 0);
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
	//get input states
	ALLEGRO_MOUSE_STATE mouseState;
	al_get_mouse_state(&mouseState);

	ALLEGRO_KEYBOARD_STATE keyboardState;
	al_get_keyboard_state(&keyboardState);


	//if (al_mouse_button_down(&mouseState, 1))//left mouse click
	//{
	//	mStartPos = Vector2D(mouseState.x, mouseState.y);

	//	GameMessage* pMessage = new PathToMessage(mStartPos, mGoalPos);
	//	gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	//}

	//if (al_mouse_button_down(&mouseState, 2))//right mouse click
	//{
	//	mGoalPos = Vector2D(mouseState.x, mouseState.y);

	//	GameMessage* pMessage = new PathToMessage(mStartPos, mGoalPos);
	//	gpGameApp->getMessageManager()->addMessage(pMessage, 0);
	//}

	while (!al_event_queue_is_empty(mpEventQueue))
	{
		al_wait_for_event(mpEventQueue, &mEvent);

		if (mEvent.type == ALLEGRO_EVENT_KEY_DOWN) //look for keyboard events
		{
			switch (gpGameApp->getState())
			{
			case GameState::MAIN_MENU:
				if (mEvent.keyboard.keycode == ALLEGRO_KEY_DOWN)
				{
					GameMessage* pMessage = new ChangeMenuSelectionMessage(true, true);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}

				if (mEvent.keyboard.keycode == ALLEGRO_KEY_UP)
				{
					GameMessage* pMessage = new ChangeMenuSelectionMessage(false, true);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}

				if (mEvent.keyboard.keycode == ALLEGRO_KEY_ENTER)
				{
					//Determining what option is currently selected, now in an if because apparently switch statements break the messaging system.
					if (gpGameApp->getMainMenu()->getSelection() == MainSelectionState::PLAY)
					{
						GameMessage* pMessage = new ChangeStateMessage(GameState::PLAYING);
						gpGameApp->getMessageManager()->addMessage(pMessage, 0);
					}
					else if (gpGameApp->getMainMenu()->getSelection() == MainSelectionState::HELP)
					{
						GameMessage* pMessage = new ChangeStateMessage(GameState::HELP_MENU);
						gpGameApp->getMessageManager()->addMessage(pMessage, 0);
					}
					else if (gpGameApp->getMainMenu()->getSelection() == MainSelectionState::CREDITS)
					{
						GameMessage* pMessage = new ChangeStateMessage(GameState::CREDITS_MENU);
						gpGameApp->getMessageManager()->addMessage(pMessage, 0);
					}
					else if (gpGameApp->getMainMenu()->getSelection() == MainSelectionState::QUIT)
					{
						GameMessage* pMessage = new ExitGameMessage();
						gpGameApp->getMessageManager()->addMessage(pMessage, 0);
					}					
				}
				break;

			case GameState::PLAYING:
				//Player Input keyboard events
				if (mEvent.keyboard.keycode == ALLEGRO_KEY_UP) //For if the player hits the up arrow
				{
					GameMessage* pMessage = new ChangePlayerDirectionMessage(0);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}

				if (mEvent.keyboard.keycode == ALLEGRO_KEY_RIGHT)
				{
					GameMessage* pMessage = new ChangePlayerDirectionMessage(1);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}

				if (mEvent.keyboard.keycode == ALLEGRO_KEY_DOWN)
				{
					GameMessage* pMessage = new ChangePlayerDirectionMessage(2);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}

				if (mEvent.keyboard.keycode == ALLEGRO_KEY_LEFT)
				{
					GameMessage* pMessage = new ChangePlayerDirectionMessage(3);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}

				if (mEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					//exit main game loop
					GameMessage* pMessage = new ChangeStateMessage(GameState::MAIN_MENU);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}
				break;
			case GameState::HELP_MENU:
				if (mEvent.keyboard.keycode == ALLEGRO_KEY_ENTER)
				{
					GameMessage* pMessage = new ChangeStateMessage(GameState::MAIN_MENU);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}
				break;

			case GameState::CREDITS_MENU:
				if (mEvent.keyboard.keycode == ALLEGRO_KEY_ENTER)
				{
					GameMessage* pMessage = new ChangeStateMessage(GameState::MAIN_MENU);
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}
				break;

			case GameState::END:
				if (mEvent.keyboard.keycode == ALLEGRO_KEY_ESCAPE)
				{
					GameMessage* pMessage = new ExitGameMessage();
					gpGameApp->getMessageManager()->addMessage(pMessage, 0);
				}
				break;
			}
		}
	}
}

void InputManager::cleanUp()
{
	al_destroy_event_queue(mpEventQueue);
}