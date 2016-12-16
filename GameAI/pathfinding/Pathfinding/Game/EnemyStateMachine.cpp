#include "EnemyStateMachine.h"
#include "FiniteStateMachine.h"
#include "Enemy.h"
#include "UnitManager.h"

State::~State()
{

}

void State::addTransition(StateTransition* pTransition)
{
	mTransitions[pTransition->getTransitionType()] = pTransition;
}

void EnemyStateMachine::addState(State* pState)
{
	mStates[pState->getID()] = pState;
}

void EnemyStateMachine::start()
{
	mInitialStateID = TransitionType::WANDER_TRANSITION;
	mpCurrentState = new Wander(0);
}

void EnemyStateMachine::update()
{
	StateTransition* pTransition = mpCurrentState->update();
}