#include "UnitManager.h"

#include "Game.h"
#include "GameApp.h"
#include "GraphicsSystem.h"
#include "SpriteManager.h"
#include "Grid.h"

#include <time.h>
#include <stdlib.h>
#include <sstream>
#include <memory>

UnitManager::UnitManager()
{
	mUnitCount = 0;
	mpUnitList = new std::map<std::string, KinematicUnit*>;

	//init shared pointers
	mPtr = std::make_shared<float>(10.0f);
	mMaxVel = std::make_shared<float>(100.0f);
}

UnitManager::~UnitManager()
{
	cleanUp();
}

//will expand this function later
void UnitManager::spawnEnemies(Grid* pGrid)
{
	std::stringstream ss;

	for (int i = 0; i < pGrid->getSize(); ++i)
	{
		if (pGrid->getValueAtIndex(i) == ENEMY_SPAWN)
		{
			ss << "Enemy" << mUnitCount;
			mUnitCount++;

			addUnit(gpGameApp->getSpriteManager()->getSprite(ENEMY_SPRITE_ID), pGrid->getULCornerOfSquare(i), Vector2D(0, 0), mMaxVel, mPtr, mPtr, 1.0f,ss.str(), false);
			dynamic_cast<Enemy*>(getUnit(ss.str()))->setGrid(pGrid);

			ss.str("");
		}
	}
}

std::vector<Enemy*> UnitManager::getEnemyList()
{
	std::vector<Enemy*> enemyList;

	for (std::map<std::string, KinematicUnit*>::iterator i = mpUnitList->begin(); i != mpUnitList->end(); ++i)
	{
		//if the unit is not an enemy that isn't active, draw it.
		if (i->first.substr(0, 5) == "Enemy")
		{
			enemyList.push_back(dynamic_cast<Enemy*>(i->second));
		}
	}

	return enemyList;
}

void UnitManager::setEnemyActive(Grid* pGrid)
{
	std::stringstream ss;

	for (int i = 0; i < mUnitCount; ++i)
	{
		ss << "Enemy" << i;
		dynamic_cast<Enemy*>(getUnit(ss.str()))->isActive(pGrid);
		ss.str("");
	}
}

void UnitManager::addUnit(Sprite* sprite, Vector2D& pos, Vector2D& vel, std::shared_ptr<float> maxVel, std::shared_ptr<float> reactionRadius
	, std::shared_ptr<float> maxRotational, float maxAccel, std::string id, bool isPlayer)
{
	//mpUnitList->emplace(id, new KinematicUnit(sprite, pos, 1, vel, 0.0f, maxVel, reactionRadius, maxRotational, maxAccel, isPlayer));
	if (isPlayer)
		mpUnitList->emplace(id, new Player(sprite, pos, 0, vel, 0.0f, maxVel, reactionRadius, maxRotational, maxAccel));
	else
		mpUnitList->emplace(id, new Enemy(sprite, pos, 0, vel, 0.0f, maxVel, reactionRadius, maxRotational, maxAccel));

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
		//if the unit is not an enemy that isn't active, draw it.
		if (!(i->first.substr(0, 5) == "Enemy" && (!dynamic_cast<Enemy*>(i->second)->getActive() || dynamic_cast<Enemy*>(i->second)->getDead())))
		{
			i->second->draw(gpGame->getGraphicsSystem()->getBackBuffer());
		}		
	}
}

void UnitManager::update(float timePassed)
{
	for (std::map<std::string, KinematicUnit*>::iterator i = mpUnitList->begin(); i != mpUnitList->end(); ++i)
	{
		//if the unit is not an enemy that is dead, update it
		if ((i->first.substr(0, 5) == "Enemy" && dynamic_cast<Enemy*>(i->second)->getDead()) == false)
		{
			i->second->update(timePassed);
		}		
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