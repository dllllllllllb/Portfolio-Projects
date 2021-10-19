//Author: Maciej Dowbor
//Last Accessed: 19/10/2021

#ifndef AUDIO_H
#define AUDIO_H

#include "AudioSettings.h"
#include "MusicEnum.h"
#include "SFML/Audio.hpp"
#include "SFXEnum.h"
#include "MovementSFXEnum.h"
#include "Macros.h"

//===========================================================================================
//Description: Stores and handles audio
//===========================================================================================
struct Audio
{
	MusicEnum m_musicTypePlaying;
	int m_musicIndexPlaying;

	//Music
	sf::Music m_combatMusic[AudioSettings::c_numOfCombatMusic];
	sf::Music m_townMusic[AudioSettings::c_numOfTownMusic];
	sf::Music m_mapMusic;
	sf::Music m_menuMusic;

	//UI SFX
	sf::SoundBuffer m_buildTown;
	sf::SoundBuffer m_buttonPress;

	//Game SFX
	sf::SoundBuffer m_heroMovement;
	sf::SoundBuffer m_newDay;
	sf::SoundBuffer m_newWeek;
	sf::SoundBuffer m_pickup;

	sf::Sound m_SFXSound;
	sf::Sound m_movementSFX;

	//===========================================================================================
	//Description: Class constructor
	//===========================================================================================
	Audio();

	//===========================================================================================
	//Description: Class destructor
	//===========================================================================================
	~Audio();

	//===========================================================================================
	//Description: Loads audio to memory / sets file paths to stream files that are too big
	//===========================================================================================
	void loadAudio();

	//===========================================================================================
	//Description: Plays music based on passed paramaters
	//===========================================================================================
	void playMusic(const MusicEnum& musicType, const int& musicIndex);

	//===========================================================================================
	//Description: Stops current music
	//===========================================================================================
	void stopCurrentlyPlayingMusic();

	//===========================================================================================
	//Description: Plays SFX, doesn't need to be stopped manually as its not looped
	//===========================================================================================
	void playSFX(const SFXEnum& SFX);

	//===========================================================================================
	//Description: Plays movement SFX, needs to be stopped manually as its looped
	//===========================================================================================
	void playMovementSFX(const MovementSFXEnum& SFX);

	//===========================================================================================
	//Description: Stops movement SFX
	//===========================================================================================
	void stopMovementSFX();

};


#endif // !AUDIOMANAGER_H

