#pragma once

#include "FiniteStateMachine.h"
#include "Enemy.h"

enum TransitionType
{
	WANDER_TRANSITION = 0,
	CHASE_TRANSITION = 1,
	FLEE_TRANSITION = 2
};

struct Chase : public State
{
	Chase(const SM_idType& id) :State(id) {};

	virtual void onEntrance(Enemy* me)
	{
		std::cout << "\nEntering Chase State: " << mID << std::endl;
		//chase the player state

	};
	virtual void onExit(Enemy* me)
	{
		std::cout << "\nExiting Chase State: " << mID << std::endl;
	};
	virtual StateTransition* update()
	{
		std::cout << "Updating Chase" << std::endl;
	};
};

struct Wander : public State
{
	Wander(const SM_idType& id) :State(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
};

struct Flee : public State
{
	Flee(const SM_idType& id) :State(id) {};

	virtual void onEntrance();
	virtual void onExit();
	virtual StateTransition* update();
};

class EnemyStateMachine : public FiniteStateMachine
{
private:
public:
};