#pragma once

#include "KinematicUnit.h"

class Player : public KinematicUnit
{
private:
	bool mAlmightyCandy; //Boolean to determine if the player has eaten the almighty candy recently

public:
	void update(float time); //Update function for the Player
	bool getIsCandied() { return mAlmightyCandy; };
};