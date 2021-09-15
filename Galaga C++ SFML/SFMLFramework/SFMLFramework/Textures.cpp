#include "Textures.h"

Textures::Textures( )
{
	loadTextures( );
	createTextures( );
}

Textures::~Textures( )
{
}

void Textures::loadTextures( )
{
	ASSERT( m_enemyShooter		.loadFromFile( "Assets/Sprites/EnemyShooter1.png" ) );
	ASSERT( m_enemyKamikaze		.loadFromFile( "Assets/Sprites/EnemyKamikaze1.png" ) );
	ASSERT( m_enemyTank			.loadFromFile( "Assets/Sprites/EnemyTank1.png" ) );
	ASSERT( m_enemyElite		.loadFromFile( "Assets/Sprites/EnemyElite1.png" ) );
	ASSERT( m_enemyBoss			.loadFromFile( "Assets/Sprites/EnemyBoss1.png" ) );
	ASSERT( m_player			.loadFromFile( "Assets/Sprites/Player1.png" ) );
	ASSERT( m_bullet			.loadFromFile( "Assets/Sprites/Bullet1.png" ) );
	ASSERT( m_healthDrop		.loadFromFile( "Assets/Sprites/HealthDrop1.png" ) );
	ASSERT( m_shieldDrop		.loadFromFile( "Assets/Sprites/ShieldDrop1.png" ) );
	ASSERT( m_creditDrop		.loadFromFile( "Assets/Sprites/CreditsDrop1.png" ) );
	ASSERT( m_bombDrop			.loadFromFile( "Assets/Sprites/BombDrop1.png" ) );
	ASSERT( m_healthShopIcon	.loadFromFile( "Assets/Sprites/HealthShopIcon.png" ) );
	ASSERT( m_shieldShopIcon	.loadFromFile( "Assets/Sprites/ShieldShopIcon.png" ) );
	ASSERT( m_speedShopIcon		.loadFromFile( "Assets/Sprites/SpeedShopIcon.png" ) );
	ASSERT( m_rateOfFireShopIcon.loadFromFile( "Assets/Sprites/RateOfFireShopIcon.png" ) );
	ASSERT( m_doubleShotShopIcon.loadFromFile( "Assets/Sprites/DoubleShotIcon.png" ) );
	ASSERT( m_TripleShotShopIcon.loadFromFile( "Assets/Sprites/TripleShotIcon.png" ) );
	ASSERT( m_QuadraShotShopIcon.loadFromFile( "Assets/Sprites/QuadraShotIcon.png" ) );
	ASSERT( m_button			.loadFromFile( "Assets/Sprites/buttonBackground.png" ) );
	ASSERT( m_tutorial			.loadFromFile( "Assets/Sprites/Tutorial.png" ) );

	ASSERT( m_font				.loadFromFile( "Assets/Fonts/Pixellari.ttf" ) );
	ASSERT( m_menuFont			.loadFromFile( "Assets/Fonts/8-BIT WONDER.TTF" ) );

	m_enemyShooter		.setSmooth( true );
	m_enemyKamikaze		.setSmooth( true );
	m_enemyTank			.setSmooth( true );
	m_enemyElite		.setSmooth( true );
	m_enemyBoss			.setSmooth( true );
	m_player			.setSmooth( true );
	m_bullet			.setSmooth( true );
	m_healthDrop		.setSmooth( true );
	m_shieldDrop		.setSmooth( true );
	m_creditDrop		.setSmooth( true );
	m_bombDrop			.setSmooth( true );
	m_healthShopIcon	.setSmooth( true );
	m_shieldShopIcon	.setSmooth( true );
	m_speedShopIcon		.setSmooth( true );
	m_rateOfFireShopIcon.setSmooth( true );
	m_doubleShotShopIcon.setSmooth( true );
	m_TripleShotShopIcon.setSmooth( true );
	m_QuadraShotShopIcon.setSmooth( true );
	m_button			.setSmooth( true );
}

void Textures::createTextures( )
{
	//Creates star texture by making a 4 by 4 pixels texture sheet
	//Creates an array of pixel values
	//Using a nested loop, fills in the contents of the pixel value array

	ASSERT( m_star.create( 4, 4 ) );

	sf::Uint8 pixels[4 * 4 * 4];				//Width * height * (RGB + Alpha)

	for( int i = 0; i < 16; i++ )				//16 == num of pixels
	{
		for( int j = 0; j < 4; j++ )            //Key: j == 0: Red
		{                                       //     j == 1: Green
			pixels[i + j] = 255;				//     j == 2: Blue
		}                                       //     j == 3: Alpha
	}

	m_star.update( pixels ); //Updates the textures with new pixel values
}