#pragma once

#include "Trackable.h"

class Menu : public Trackable
{
private:
	int mNumOptions;	//Integer for the number of options on the menu
public:
	Menu() {};
	~Menu() {};

	virtual void update(float timePassed) = 0;

	inline int getNumOptions() { return mNumOptions; };
};