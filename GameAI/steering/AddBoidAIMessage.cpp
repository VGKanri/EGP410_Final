#include "AddBoidAIMessage.h"

#include "Game.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "StateManager.h"

AddBoidAIMessage::AddBoidAIMessage()
:GameMessage(ADD_DYNAMIC_ARRIVE_AI_MESSAGE)
{

}

AddBoidAIMessage::~AddBoidAIMessage()
{

}

void AddBoidAIMessage::process()
{
	std::string id;
	Vector2D pos;
	Vector2D vel;

	for (int i = 0; i < 5; ++i)
	{
		id = "ai" + std::to_string(gpGame->getUnitManager()->getUnitCount());
		pos = Vector2D(400 + (i*30), 300 + (i*30));
		vel = Vector2D(50.0f, 0.0f);

		gpGame->getUnitManager()->addUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), pos, vel, gpGame->getStateManager()->getVelocity(), gpGame->getStateManager()->getRadius(), gpGame->getStateManager()->getAngularVelocity(), 100.0f, id);
		gpGame->getUnitManager()->setUnitBehavior(BOID, id, "");
	}	
}