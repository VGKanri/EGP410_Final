#pragma once

#include "Trackable.h"
#include <map>
#include <string>

class Song;
class SoundEffect;

const std::string BOINGBURG_PATH = "../Assets/Boingburg.ogg";
const std::string BATTLE_THEME_PATH = "../Assets/BattleTheme.ogg";
const std::string TITLE_THEME_PATH = "../Assets/TitleTheme.ogg";
const std::string POWER_UP_PATH = "../Assets/PowerUp.ogg";

const std::string COIN_EFFECT_PATH = "../Assets/coin.wav";
const std::string STAIR_EFFECT_PATH = "../Assets/stairs.wav";
const std::string POWERUP_EFFECT_PATH = "../Assets/powerUp.wav";

const std::string BOINGBURG_KEY = "boingburg";
const std::string BATTLE_THEME_KEY = "battle_theme";
const std::string TITLE_THEME_KEY = "title_theme";
const std::string POWER_UP_KEY = "power_up";

const std::string COIN_KEY = "coin";
//const std::string STAIR_KEY = "stairs";
const std::string POWER_EFFECT_KEY = "power_effect";

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