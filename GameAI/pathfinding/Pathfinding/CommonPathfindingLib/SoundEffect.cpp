#include "SoundEffect.h"

void SoundEffect::play()
{
	al_play_sample(mpSample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mID);
}