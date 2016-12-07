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

void UnitManager::addUnit(Sprite* sprite, Vector2D& pos, Vector2D& vel, std::shared_ptr<float> maxVel, std::shared_ptr<float> reactionRadius
	, std::shared_ptr<float> maxRotational, float maxAccel, std::string id, bool isPlayer)
{
	//mpUnitList->emplace(id, new KinematicUnit(sprite, pos, 1, vel, 0.0f, maxVel, reactionRadius, maxRotational, maxAccel, isPlayer));
	if (isPlayer)
		mpUnitList->emplace(id, new Player(sprite, pos, 0, vel, 0.0f, maxVel, reactionRadius, maxRotational, maxAccel));
}

void UnitManager::removeUnit(std::string id)
{
	delete mpUnitList->at(id);
	mpUnitList->erase(id);
}

KinematicUnit* UnitManager::getUnit(std::string id)
{
	return mpUnitList->at(id);
}

void UnitManager::draw()
{
	for (std::map<std::string, KinematicUnit*>::iterator i = mpUnitList->begin(); i != mpUnitList->end(); ++i)
	{
		i->second->draw(gpGame->getGraphicsSystem()->getBackBuffer());
	}
}

void UnitManager::update(float timePassed)
{
	for (std::map<std::string, KinematicUnit*>::iterator i = mpUnitList->begin(); i != mpUnitList->end(); ++i)
	{
		i->second->update(timePassed);
	}
	draw();
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