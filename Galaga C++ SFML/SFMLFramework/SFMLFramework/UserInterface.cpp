//Author: Maciej Dowbor
//Module: MED5149
//Date last accessed: 20/01/2021

#include "UserInterface.h"

UserInterface::UserInterface( sf::RenderWindow &window, HighScoreTable *highScoreTable ) :
	m_window			( window ),
	m_pHighScoreTable	( highScoreTable ),
	m_playerScore		( 0 ),
	m_isDefeat			( false ),
	m_isVictory			( false )
{
	ASSERT( m_font.loadFromFile( "Assets/Fonts/8-BIT WONDER.TTF" ) );

	//Health
	m_health.setString( "Health 3" );
	m_health.setFont( m_font );
	m_health.setFillColor( sf::Color::Green );
	m_health.setPosition( k_textHealthPositionX, k_UIPositionY );

	//Shield
	m_shield.setString( "Shield 3" );
	m_shield.setFont( m_font );
	m_shield.setFillColor( sf::Color::Blue );
	m_shield.setPosition( k_textShieldPositionX, k_UIPositionY );

	//Credits
	m_credits.setString( "Credits 0" );
	m_credits.setFont( m_font );
	m_credits.setFillColor( sf::Color::Yellow );
	m_credits.setPosition( k_textCreditsPositionX, k_UIPositionY );

	//Wave number
	m_wave.setString( "Wave 1" );
	m_wave.setFont( m_font );
	m_wave.setPosition( k_textWavePositionX, k_UIPositionY );

	//Score
	m_score.setString( "Score 0" );
	m_score.setFont( m_font );
	m_score.setPosition( k_textScorePositionX, k_UIPositionY );

	//Defeat
	m_defeat.setString( "DEFEAT" );
	m_defeat.setFont( m_font );
	m_defeat.setCharacterSize( k_bannerTextSize );
	m_defeat.setFillColor( sf::Color::Red );
	m_defeat.setOrigin( m_defeat.getLocalBounds( ).width * 0.5f, m_defeat.getLocalBounds( ).height * 0.5f );
	m_defeat.setPosition( k_bannerTextPosition );

	//Victory
	m_victory.setString( "VICTORY" );
	m_victory.setFont( m_font );
	m_victory.setCharacterSize( k_bannerTextSize );
	m_victory.setFillColor( sf::Color::Green );
	m_victory.setOrigin( m_victory.getLocalBounds( ).width * 0.5f, m_victory.getLocalBounds( ).height * 0.5f );
	m_victory.setPosition( k_bannerTextPosition );

	//Final Score
	m_finalScore.setString( "Final Score" );
	m_finalScore.setFont( m_font );
	m_finalScore.setCharacterSize( k_scoreAndInstructionsSize );
	m_finalScore.setOrigin( m_finalScore.getLocalBounds( ).width * 0.5f, m_finalScore.getLocalBounds( ).height * 0.5f );
	m_finalScore.setPosition( k_finalScoreTextPosition );

	//Instructions
	m_Instructions.setString( "Press enter to return to main menu" );
	m_Instructions.setFont( m_font );
	m_Instructions.setCharacterSize( k_scoreAndInstructionsSize );
	m_Instructions.setOrigin( m_Instructions.getLocalBounds( ).width * 0.5f, m_Instructions.getLocalBounds( ).height * 0.5f );
	m_Instructions.setPosition( k_instructionsTextPosition );
}

UserInterface::~UserInterface( )
{
}

void UserInterface::drawUI( )
{
	m_window.draw( m_health );
	m_window.draw( m_shield );
	m_window.draw( m_credits );
	m_window.draw( m_wave );
	m_window.draw( m_score );

	if( m_isDefeat )
	{
		m_window.draw( m_defeat );
		m_window.draw( m_finalScore );
		m_window.draw( m_Instructions );

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Enter ) )
		{
			g_gameState = GameState::menu;
		}
	}

	if( m_isVictory )
	{
		m_window.draw( m_victory );
		m_window.draw( m_finalScore );
		m_window.draw( m_Instructions );

		if( sf::Keyboard::isKeyPressed( sf::Keyboard::Key::Enter ) )
		{
			g_gameState = GameState::menu;
		}
	}
}

void UserInterface::updateText( const UIVariable &variable, const int &value )
{
	switch( variable )
	{
		case UIVariable::health:
		m_health.setString( "Health " + std::to_string( value ) );
		break;

		case UIVariable::shield:
		m_shield.setString( "Shield " + std::to_string( value ) );
		break;

		case UIVariable::credits:
		m_credits.setString( "Credits " + std::to_string( value ) );
		break;

		case UIVariable::wave:
		m_wave.setString( "Wave " + std::to_string( value ) );
		break;

		case UIVariable::score:
		m_score.setString( "Score " + std::to_string( value ) );
		m_playerScore = value;
		break;

		default:
		break;
	}
}

UserInterface *UserInterface::getUserInterface( )
{
	return this;
}

void UserInterface::toggleDefeat( )
{
	m_isDefeat = !m_isDefeat;
	m_finalScore.setString( "Final " + m_score.getString( ) );
	m_finalScore.setOrigin( m_finalScore.getLocalBounds( ).width * 0.5f, m_finalScore.getLocalBounds( ).height * 0.5f );
	m_finalScore.setPosition( k_finalScoreTextPosition );
	m_pHighScoreTable->sortTable( "Player", m_playerScore );
}

void UserInterface::toggleVictory( )
{
	m_isVictory = !m_isVictory;
	m_finalScore.setString( "Final " + m_score.getString( ) );
	m_finalScore.setOrigin( m_finalScore.getLocalBounds( ).width * 0.5f, m_finalScore.getLocalBounds( ).height * 0.5f );
	m_finalScore.setPosition( k_finalScoreTextPosition );
	m_pHighScoreTable->sortTable( "Player", m_playerScore );
}

void UserInterface::reset( )
{
	m_isDefeat = false;
	m_isVictory = false;
	m_playerScore = 0;

	m_health.setString( "Health 3" );
	m_shield.setString( "Shield 3" );
	m_credits.setString( "Credits 0" );
	m_wave.setString( "Wave 1" );
	m_score.setString( "Score 0" );
}