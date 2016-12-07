#pragma once

#include "Trackable.h"
#include <map>
#include <string>

class Song;
class SoundEffect;

const std::string BOINGBURG_PATH = "../Assets/boingburg.ogg";

const std::string BOINGBURG_KEY = "boingburg";

/*A sound manager class that is in charge of handling all songs and sound effects,
	including loading samples, playing them, stopping them, and deleting them.*/

class SoundManager : public Trackable
{
public:
	SoundManager();
	~SoundManager();

	void init();

	void cleanUp();

	void playSong(std::string key);
	void stopSong();

	void playSoundEffect(std::string key);

private:
	std::map<std::string, SoundEffect*> mpSoundEffects;
	std::map<std::string, Song*> mpSongs;

	Song* mpCurrentSong;
};