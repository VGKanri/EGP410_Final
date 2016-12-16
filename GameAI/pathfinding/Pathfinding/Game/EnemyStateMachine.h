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

	void onEntrance(Enemy* me)
	{
		std::cout << "\nEntering Chase State: " << mID << std::endl;
		//chase the player state

	};
	void onExit()
	{
		std::cout << "\nExiting Chase State: " << mID << std::endl;
	};
	StateTransition* update()
	{
		std::cout << "Updating Chase" << std::endl;
	};
};

struct Wander : public State
{
	Wander(const SM_idType& id) :State(id) {};

	void onEntrance(Enemy* me)
	{
		std::cout << "\nEntering Wander State: " << mID << std::endl;
		//chase the player state

	};
	void onExit()
	{
		std::cout << "\nExiting Wander State: " << mID << std::endl;
	};
	StateTransition* update()
	{
		std::cout << "Updating Wander" << std::endl;
	};
};

struct Flee : public State
{
	Flee(const SM_idType& id) :State(id) {};

	void onEntrance(Enemy* me)
	{
		std::cout << "\nEntering Flee State: " << mID << std::endl;
		//chase the player state

	};
	void onExit()
	{
		std::cout << "\nExiting Flee State: " << mID << std::endl;
	};
	StateTransition* update()
	{
		std::cout << "Updating Flee" << std::endl;
	};
};

class EnemyStateMachine : public FiniteStateMachine
{
public:
	EnemyStateMachine() :mpCurrentState(NULL), mInitialStateID(-1) {};
	~EnemyStateMachine() {};

	void addState(State* pState);
	void setInitialStateID(const SM_idType& id) { mInitialStateID = id; };

	void update();//give the current state a chance to run
	void start();//go to the initial state

protected:
	void transitionToState(const SM_idType& targetID);//call onExit for old state and onEntrance for the new state

	std::map<SM_idType, State*> mStates;//all states indexed by stateID
	State* mpCurrentState;//the current state that is running
	SM_idType mInitialStateID;//the id of the state which should run first
};