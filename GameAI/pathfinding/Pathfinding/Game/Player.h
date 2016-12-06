#pragma once

#include "KinematicUnit.h"

enum CURRENT_DIRECTION
{
	UP = 0,
	RIGHT = 1,
	DOWN = 2,
	LEFT = 3
};

class Player : public KinematicUnit
{
private:
	bool mAlmightyCandy; //Boolean to determine if the player has eaten the almighty candy recently
	CURRENT_DIRECTION mDirection;

public:
	void update(float time); //Update function for the Player

	bool getIsCandied() { return mAlmightyCandy; };
	inline CURRENT_DIRECTION& getCurrentDirection() { return mDirection; };
};