#pragma once

#include "Trackable.h"
#include <map>

class StateTransition;

typedef int SM_idType;

//Struct that serves as the base state class
struct State
{
	State(const SM_idType& id) :mID(id) {};
	~State();

	void addTransition(StateTransition* pTransition);
	inline const SM_idType& getID() const { return mID; };

	virtual void onEntrance(Enemy* me) = 0;
	virtual void onExit() = 0;

	virtual StateTransition* update() = 0;
protected: 
	SM_idType mID;
	std::map<TransitionType, StateTransition*> mTransitions;
};

class FiniteStateMachine : public Trackable
{
protected:
	State* mpCurrentState; //The current state of the state machine
	std::map<SM_idType, State*> mStates;
	SM_idType mInitialStateID;

	void transitionToState(const SM_idType& targetID);
public:
	FiniteStateMachine() {};
	~FiniteStateMachine() {};

	void addState(State* pState);
	void setInitialStateID(const SM_idType& id) { mInitialStateID = id; };

	void update();
	void start();
};

class StateTransition : public Trackable
{
	StateTransition(TransitionType type, const SM_idType& targetID) :mType(type), mTargetStateID(targetID) {};
	~StateTransition() {};

	int getTargetStateID() const { return mTargetStateID; };
	TransitionType getTransitionType() const { return mType; };

protected:
	SM_idType mTargetStateID;
	TransitionType mType;
};

