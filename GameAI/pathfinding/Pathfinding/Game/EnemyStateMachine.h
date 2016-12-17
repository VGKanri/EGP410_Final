#pragma once

#include "FiniteStateMachine.h"
#include "GameApp.h"

/*
Class for the enemy state machine, derived from the state machine class
*/

class UnitManager;
class Enemy;


//Struct for the chase state
struct Chase : public State
{
	Chase(const SM_idType& id) :State(id) {};
	std::map<TransitionType, StateTransition*> mTransitions;

	void onEntrance(Enemy* me);
	void onExit(Enemy* me);
	StateTransition* update(Enemy* me);
};

struct Wander : public State
{
	Wander(const SM_idType& id) :State(id) {};
	std::map<TransitionType, StateTransition*> mTransitions;

	void onEntrance(Enemy* me);
	void onExit(Enemy* me);
	StateTransition* update(Enemy* me);
};

struct Flee : public State
{
	Flee(const SM_idType& id) :State(id) {};
	std::map<TransitionType, StateTransition*> mTransitions;

	void onEntrance(Enemy* me);
	void onExit(Enemy* me);
	StateTransition* update(Enemy* me);
};

class EnemyStateMachine : public FiniteStateMachine
{
public:
	EnemyStateMachine():mpCurrentState(NULL), mInitialStateID(-1) {};
	~EnemyStateMachine() {};

	void addState(State* pState);
	void setInitialStateID(const SM_idType& id) { mInitialStateID = id; };

	void update(Enemy* me);//give the current state a chance to run
	void start();//go to the initial state

	std::map<SM_idType, State*> mStates;//all states indexed by stateID


protected:
	void transitionToState(const SM_idType& targetID, Enemy* me);//call onExit for old state and onEntrance for the new state

	State* mpCurrentState;//the current state that is running
	SM_idType mInitialStateID;//the id of the state which should run first
};