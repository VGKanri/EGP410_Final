#include "SoundManager.h"
#include "Song.h"
#include "SoundEffect.h"

SoundManager::SoundManager()
{

}

SoundManager::~SoundManager()
{
	cleanUp();
}

//load in all needed audio files
void SoundManager::init()
{
	mpSongs.emplace(BOINGBURG_KEY, new Song(BOINGBURG_PATH));
}

void SoundManager::cleanUp()
{
	for (auto &iter : mpSongs)
	{
		delete iter.second;
	}

	for (auto &iter : mpSoundEffects)
	{
		delete iter.second;
	}
}

void SoundManager::playSong(std::string key)
{
	mpSongs.at(key)->play();
	mpCurrentSong = mpSongs.at(key);
}

void SoundManager::stopSong()
{
	mpCurrentSong->stop();
}

void SoundManager::playSoundEffect(std::string key)
{
	mpSoundEffects.at(key)->play();
}
