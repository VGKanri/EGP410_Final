#include "SoundEffect.h"

SoundEffect::SoundEffect(std::string filePath):
Song(filePath)
{

}

void SoundEffect::play()
{
	al_play_sample(mpSample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, &mID);
}