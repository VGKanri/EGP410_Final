#pragma once

#include "Trackable.h"
#include "Sprite.h"
#include "Animation.h"

class Menu : public Trackable
{
private:
	int mNumOptions;	//Integer for the number of options on the menu

	//Animation for the selector
	Animation* mpAnimation;
	Sprite* mpSprite;
public:
	Menu() {};
	~Menu() {};

	virtual void update(float timePassed) = 0;

	inline int getNumOptions() { return mNumOptions; };

	inline void setAnimation(Animation* anim) { mpAnimation = anim; };
	inline void setSprite(Sprite* sprite) { mpSprite = sprite; };

	inline Sprite* getSprite() { return mpSprite; };
	inline Animation* getAnimation() { return mpAnimation; };
};