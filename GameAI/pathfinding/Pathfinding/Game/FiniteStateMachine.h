#pragma once

#include "Trackable.h"

//Struct that serves as the base state class
struct State
{
	State* changeState(int stateNum);
private: 
	int thisState;
};

class FiniteStateMachine : public Trackable
{
private:
	State* currentState; //The current state of the state machine
public:
};