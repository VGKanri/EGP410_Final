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

void EnemyStateMachine::update(Enemy* me)
{
	if (mpCurrentState == NULL)
	{
		start();
	}

	StateTransition* pTransition = mpCurrentState->update(me);
	if (pTransition != NULL)
	{
		transitionToState(pTransition->getTargetStateID(), me);
	}
}

void EnemyStateMachine::transitionToState(const SM_idType& targetID, Enemy* me)
{
	if (mpCurrentState != NULL)
	{
		mpCurrentState->onExit(me);
	}

	mpCurrentState = mStates[targetID];
	if (mpCurrentState != NULL)
	{
		mpCurrentState->onEntrance(me);
	}
}

StateTransition* Wander::update(Enemy* me)
{
	//If the player is close enough to the player
	bool mPlayerNearby = me->getInRadius();
	if (mPlayerNearby && !gpGameApp->getUnitManager()->getPlayer()->getIsCandied())
	{
		std::map<TransitionType, StateTransition*>::iterator iter = me->getStateMachine()->mStates[0]->mTransitions.find(CHASE_TRANSITION);
		if (iter != me->getStateMachine()->mStates[0]->mTransitions.end())
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}

	//If the player is close enough to the player
	if (mPlayerNearby && gpGameApp->getUnitManager()->getPlayer()->getIsCandied())
	{
		std::map<TransitionType, StateTransition*>::iterator iter = me->getStateMachine()->mStates[0]->mTransitions.find(FLEE_TRANSITION);
		if (iter != me->getStateMachine()->mStates[0]->mTransitions.end())
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	return NULL;
	return NULL;
}

StateTransition* Flee::update(Enemy* me)
{
	//If the player is close enough to the player
	bool mPlayerNearby = me->getInRadius();
	if (!mPlayerNearby)
	{
		std::map<TransitionType, StateTransition*>::iterator iter = me->getStateMachine()->mStates[0]->mTransitions.find(WANDER_TRANSITION);
		if (iter != me->getStateMachine()->mStates[0]->mTransitions.end())
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	if (mPlayerNearby && !gpGameApp->getUnitManager()->getPlayer()->getIsCandied())
	{
		std::map<TransitionType, StateTransition*>::iterator iter = me->getStateMachine()->mStates[0]->mTransitions.find(CHASE_TRANSITION);
		if (iter != me->getStateMachine()->mStates[0]->mTransitions.end())
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	return NULL;
}

StateTransition* Chase::update(Enemy* me)
{
	//If the player is close enough to the player
	bool mPlayerNearby = me->getInRadius();
	if (!mPlayerNearby)
	{
		std::map<TransitionType, StateTransition*>::iterator iter = me->getStateMachine()->mStates[0]->mTransitions.find(WANDER_TRANSITION);
		if (iter != me->getStateMachine()->mStates[0]->mTransitions.end())
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	if (mPlayerNearby && gpGameApp->getUnitManager()->getPlayer()->getIsCandied())
	{
		std::map<TransitionType, StateTransition*>::iterator iter = me->getStateMachine()->mStates[0]->mTransitions.find(FLEE_TRANSITION);
		if (iter != me->getStateMachine()->mStates[0]->mTransitions.end())
		{
			StateTransition* pTransition = iter->second;
			return pTransition;
		}
	}
	return NULL;
}

void Chase::onEntrance(Enemy* me)
{
	me->setCurrentSteering(SteeringState::CHASE);
}

void Flee::onEntrance(Enemy* me)
{
	me->setCurrentSteering(SteeringState::FLEE);
}

void Wander::onEntrance(Enemy* me)
{
	me->setCurrentSteering(SteeringState::WANDER);
}

void Chase::onExit(Enemy* me)
{
}

void Flee::onExit(Enemy* me)
{
}

void Wander::onExit(Enemy* me)
{
}