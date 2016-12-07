#pragma once

#include "Song.h"

/*Subclass of Song, can do everything song does but had to override the
play function to make it not loop*/

class SoundEffect : public Song
{
public:
	void play();
};
