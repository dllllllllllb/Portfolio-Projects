#include "Audio.h"

namespace settings = AudioSettings;
Audio::Audio():
	m_musicTypePlaying(MusicEnum::none),
	m_musicIndexPlaying(0)
{
	loadAudio();
	m_SFXSound.setVolume(settings::c_SFXVolume);
	m_movementSFX.setVolume(settings::c_SFXVolume);
	m_movementSFX.setLoop(true);
}

Audio::~Audio()
{
}

void Audio::loadAudio()
{
	//Music
	
	//Combat Music
	ASSERT(m_combatMusic[0].openFromFile("Assets//Audio//Music//COMBAT01.wav"));
	ASSERT(m_combatMusic[1].openFromFile("Assets//Audio//Music//COMBAT02.wav"));
	ASSERT(m_combatMusic[2].openFromFile("Assets//Audio//Music//COMBAT03.wav"));
	ASSERT(m_combatMusic[3].openFromFile("Assets//Audio//Music//COMBAT04.wav"));
	for (int i = 0; i < settings::c_numOfCombatMusic; i++)
	{
		m_combatMusic[i].setLoop(true);
	}
	
	//Town Music
	ASSERT(m_townMusic[0].openFromFile("Assets/Audio/Music/CastleTown.wav"));
	ASSERT(m_townMusic[1].openFromFile("Assets/Audio/Music/InfernoTown.wav"));
	for (int i = 0; i < settings::c_numOfTownMusic; i++)
	{
		m_townMusic[i].setLoop(true);
	}
	
	//Map Music
	ASSERT(m_mapMusic.openFromFile("Assets/Audio/Music/GRASS.wav"));
	m_mapMusic.setLoop(true);

	//Menu Music
	ASSERT(m_menuMusic.openFromFile("Assets/Audio/Music/MAINMENU.wav"));
	m_menuMusic.setLoop(true);


	//SFX

	//UI SFX
	ASSERT(m_buildTown.loadFromFile("Assets/Audio/SFX UI/BUILDTWN.wav"));
	ASSERT(m_buttonPress.loadFromFile("Assets/Audio/SFX UI/BUTTON.wav"));

	//Game SFX
	ASSERT(m_heroMovement.loadFromFile("Assets/Audio/SFX Game/HORSE00.wav"));
	ASSERT(m_newDay.loadFromFile("Assets/Audio/SFX Game/NEWDAY.wav"));
	ASSERT(m_newWeek.loadFromFile("Assets/Audio/SFX Game/NEWWEEK.wav"));
	ASSERT(m_pickup.loadFromFile("Assets/Audio/SFX Game/PICKUP02.wav"));
}

void Audio::playMusic(const MusicEnum& musicType, const int& musicIndex)
{
	stopCurrentlyPlayingMusic();

	m_musicTypePlaying = musicType;
	m_musicIndexPlaying = musicIndex;

	sf::Music* pMusic = &m_menuMusic;

	switch (m_musicTypePlaying)
	{
		case MusicEnum::mapMusic:
			pMusic = &m_mapMusic;
			break;

		case MusicEnum::townMusic:
			pMusic = &m_townMusic[musicIndex];
			break;

		case MusicEnum::combatMusic:
			pMusic = &m_combatMusic[musicIndex];
			break;

		case MusicEnum::none:
		case MusicEnum::menuMusic: //Menu music is set as default
		default:
			break;
	}
	pMusic->setVolume(settings::c_musicVolume);
	pMusic->play();
}

void Audio::stopCurrentlyPlayingMusic()
{
	sf::Music* pMusic = &m_menuMusic;

	switch (m_musicTypePlaying)
	{
	case MusicEnum::mapMusic:
		pMusic = &m_mapMusic;
		break;
	case MusicEnum::townMusic:
		pMusic = &m_townMusic[m_musicIndexPlaying];
		break;

	case MusicEnum::combatMusic:
		pMusic = &m_combatMusic[m_musicIndexPlaying];
		break;

	case MusicEnum::none:
	case MusicEnum::menuMusic: //Menu music is set as default
	default:
		break;
	}

	pMusic->stop();
}

void Audio::playSFX(const SFXEnum& SFX)
{
	sf::SoundBuffer* tempBuffer = &m_buttonPress; 

	switch (SFX)
	{
	case SFXEnum::newDay:
		tempBuffer = &m_newDay;
		break;
	case SFXEnum::newWeek:
		tempBuffer = &m_newWeek;
		break;
	case SFXEnum::pickup:
		tempBuffer = &m_pickup;
		break;
	case SFXEnum::buildTown:
		tempBuffer = &m_buildTown;
		break;


	case SFXEnum::none:
	case SFXEnum::button: //Button is set as default
	default:
		break;
	}

	m_SFXSound.setBuffer(*tempBuffer);
	m_SFXSound.play();
}

void Audio::playMovementSFX(const MovementSFXEnum& SFX)
{
	sf::SoundBuffer* tempBuffer = &m_heroMovement;
	switch (SFX)
	{
	case MovementSFXEnum::none:
	case MovementSFXEnum::heroMovement: //Hero movement is set by default
	default:
		break;
	}

	m_movementSFX.setBuffer(*tempBuffer);
	m_movementSFX.play();
}

void Audio::stopMovementSFX()
{
	m_movementSFX.stop();
}
