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
	mpSongs.emplace(TITLE_THEME_KEY, new Song(TITLE_THEME_PATH));
	mpSongs.emplace(BATTLE_THEME_KEY, new Song(BATTLE_THEME_PATH));
	mpSongs.emplace(POWER_UP_KEY, new Song(POWER_UP_PATH));

	mpSoundEffects.emplace(COIN_KEY, new SoundEffect(COIN_EFFECT_PATH));
	//mpSoundEffects.emplace(STAIR_KEY, new SoundEffect(STAIR_EFFECT_PATH));
	mpSoundEffects.emplace(POWER_EFFECT_KEY, new SoundEffect(POWERUP_EFFECT_PATH));
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
