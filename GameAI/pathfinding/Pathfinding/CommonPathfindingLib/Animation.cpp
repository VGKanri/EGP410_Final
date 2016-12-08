#include "Animation.h"

Animation::Animation(double timing, bool loop, int startingSprite)
{
	mAnimationTiming = timing;
	mLoop = loop;
	mCurrentSprite = startingSprite;
	mCurrentTime = 0.0;
}

Animation::~Animation()
{
	for (auto &sprite : mSpriteList)
	{
		delete sprite;
	}

	mSpriteList.clear();
}

void Animation::setParameters(double timing, bool loop, int startingSprite)
{
	mAnimationTiming = timing;
	mLoop = loop;
	mCurrentSprite = startingSprite;
}

void Animation::addSpriteAt(Sprite *pSprite, int location)
{
	mSpriteList.insert(mSpriteList.begin() + location, pSprite);
}

void Animation::pushSprite(Sprite *pSprite)
{
	mSpriteList.push_back(pSprite);
}

void Animation::update(const double &deltaTime)
{
	mCurrentTime += deltaTime;

	if (mCurrentTime <= mAnimationTiming)
		return;

	mCurrentSprite++;

	if (mCurrentSprite >= static_cast<int>(mSpriteList.size()))
		mCurrentSprite = 0;

	mCurrentTime = 0.0;
}
