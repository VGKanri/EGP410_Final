#include "Song.h"

Song::Song(std::string filePath)
{
	mpSample = al_load_sample(filePath.c_str());
}

Song::~Song()
{
	al_destroy_sample(mpSample);
}

void Song::play()
{
	al_play_sample(mpSample, 1.0, 0.0, 1.0, ALLEGRO_PLAYMODE_LOOP, &mID);
}

void Song::stop()
{
	al_stop_sample(&mID);
}