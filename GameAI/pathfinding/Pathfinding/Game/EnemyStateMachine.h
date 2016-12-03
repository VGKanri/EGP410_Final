#pragma once

#include "FiniteStateMachine.h"

struct Chase : public State
{
	State changeState(int choice)
	{
		if (choice == 2)
		{
			//Code for wander trigger
		}

		else if (choice == 3)
		{
			//Code for Evade trigger
		}
	}
};

struct Wander : public State
{
};

struct Evade : public State
{
};

class EnemyStateMachine : public FiniteStateMachine
{
private:
public:
};