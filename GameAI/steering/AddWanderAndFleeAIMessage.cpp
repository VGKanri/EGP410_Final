#include "AddWanderAndFleeAIMessage.h"

#include "Game.h"
#include "UnitManager.h"
#include "SpriteManager.h"
#include "StateManager.h"

AddWanderAndFleeAIMessage::AddWanderAndFleeAIMessage()
:GameMessage(ADD_WANDER_AND_FLEE_AI_MESSAGE)
{

}

AddWanderAndFleeAIMessage::~AddWanderAndFleeAIMessage()
{

}

void AddWanderAndFleeAIMessage::process()
{
	std::string id = "ai" + std::to_string(gpGame->getUnitManager()->getUnitCount());
	Vector2D pos = Vector2D(gpGame->getUnitManager()->getUnit("player")->getPosition().getX() + 100, gpGame->getUnitManager()->getUnit("player")->getPosition().getY());
	Vector2D vel = Vector2D(0.0f, 0.0f);

	gpGame->getUnitManager()->addUnit(gpGame->getSpriteManager()->getSprite(AI_ICON_SPRITE_ID), pos, vel, gpGame->getStateManager()->getVelocity(), gpGame->getStateManager()->getRadius(), gpGame->getStateManager()->getAngularVelocity(), 100.0f, id);
	gpGame->getUnitManager()->setUnitBehavior(WANDER_AND_FLEE, id, "player");
}