#include "UnitManager.h"

#include "Game.h"
#include "GraphicsSystem.h"
#include "Sprite.h"

#include <time.h>
#include <stdlib.h>

UnitManager::UnitManager()
{
	mUnitCount = 0;
	mpUnitList = new std::map<std::string, KinematicUnit*>;
}

UnitManager::~UnitManager()
{
	cleanUp();
}

void UnitManager::addUnit(Sprite* sprite, Vector2D& pos, Vector2D& vel, std::shared_ptr<float> maxVel, std::shared_ptr<float> reactionRadius, std::shared_ptr<float> maxRotational, float maxAcc, std::string id, bool isPlayer)
{
	mpUnitList->emplace(id, new KinematicUnit(sprite, pos, 1, vel, 0.0f, maxVel, reactionRadius, maxRotational, maxAcc, isPlayer));
	mUnitCount++;
}

void UnitManager::removeUnit(std::string id)
{
	delete mpUnitList->at(id);
	mpUnitList->erase(id);
}

void UnitManager::setUnitBehavior(BehaviorType type, std::string entityID, std::string targetID)
{
	switch (type)
	{
		case DYNAMIC_ARRIVE:
			mpUnitList->at(entityID)->dynamicArrive(mpUnitList->at(targetID));
			break;
		case DYNAMIC_SEEK:
			mpUnitList->at(entityID)->dynamicSeek(mpUnitList->at(targetID));
			break;
		case WANDER_AND_SEEK:
			mpUnitList->at(entityID)->wanderAndSeek(mpUnitList->at(targetID));
			break;
		case WANDER_AND_FLEE:
			mpUnitList->at(entityID)->wanderAndFlee(mpUnitList->at(targetID));
			break;
		case BOID:
			mpUnitList->at(entityID)->boid();
			break;
	}
}

KinematicUnit* UnitManager::getUnit(std::string id)
{
	return mpUnitList->at(id);
}

bool UnitManager::deleteRandomAIUnit()
{
	std::string idCheck = "";

	//if only the player is left, tell the message to exit the game
	if (mpUnitList->size() <= 1)
	{
		return true;
	}
	else
	{
		do
		{
			auto it = mpUnitList->begin();
			std::advance(it, rand() % mpUnitList->size());

			idCheck = it->first;

			if (idCheck != "player") 
				removeUnit(idCheck);

		} while (idCheck == "player");

		return false; //continue game
	}	
}

void UnitManager::update(double timePassed)
{

	for (std::map<std::string, KinematicUnit*>::iterator i = mpUnitList->begin(); i != mpUnitList->end(); ++i)
	{
		i->second->update(timePassed);
	}
}

void UnitManager::draw()
{
	for (std::map<std::string, KinematicUnit*>::iterator i = mpUnitList->begin(); i != mpUnitList->end(); ++i)
	{
		i->second->draw(gpGame->getGraphicsSystem()->getBackBuffer());
	}
}

void UnitManager::cleanUp()
{
	for (std::map<std::string, KinematicUnit*>::iterator i = mpUnitList->begin(); i != mpUnitList->end(); ++i)
	{
		delete i->second;
	}

	mpUnitList->clear();
	delete mpUnitList;
}