#pragma once

#include <vector>
#include <Trackable.h>

class Sprite;

const double TIMING = 1.0 / 20.0;

class Animation : public Trackable
{
public:
	Animation(double timing = TIMING, bool loop = true, int startingSprite = 0);
	~Animation();

	void setParameters(double timing = TIMING, bool loop = true, int startingSprite = 0);

	inline int getAnimationLength() const { return mSpriteList.size(); };
	inline Sprite* getCurrentSprite() { return mSpriteList[mCurrentSprite]; }

	inline void resetAnimation() { mCurrentSprite = 0; }

	void addSpriteAt(Sprite *pSprite, int location);
	void pushSprite(Sprite *pSprite);

	void update(const double &deltaTime);

private:
	std::vector<Sprite*> mSpriteList;
	double mAnimationTiming;
	bool mLoop;
	int mCurrentSprite;
	double mCurrentTime;
};