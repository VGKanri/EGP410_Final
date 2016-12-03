#pragma once

#include "KinematicUnit.h"

class Player : public KinematicUnit
{
private:
	bool almightyCandy; //Boolean to determine if the player has eaten the almighty candy recently

public:
	void update(float time); //Update function for the Player

};