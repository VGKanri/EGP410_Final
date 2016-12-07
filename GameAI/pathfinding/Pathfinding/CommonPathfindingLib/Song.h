#pragma once

#include "Trackable.h"

#include <string>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/*A basic wrapper class for allegro sample. Handles loading, deletion, playing,
and stopping of an allegro sample.*/

class Song : public Trackable
{
public:
	Song(std::string filePath);
	~Song();

	virtual void play();
	void stop();

protected:
	ALLEGRO_SAMPLE* mpSample;
	ALLEGRO_SAMPLE_ID mID;
};
