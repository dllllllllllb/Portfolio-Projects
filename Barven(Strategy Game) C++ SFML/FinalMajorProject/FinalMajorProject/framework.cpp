#include "framework.h"

//Global variables decleration
GameState Global::g_gameState = GameState::menu;
sf::Event Global::g_event;
UILayerEnum Global::g_UILayer = UILayerEnum::town;
UILayerEnum Global::g_previousUILayer = g_UILayer;
bool Global::g_isWindowFocused = true;
bool Global::g_wasObjectPressed = false;
bool Global::g_wasRMBPressed = false;
bool Global::g_isLMBPressed = false;
bool Global::g_isRMBPressed = false;
bool Global::g_updateGame = true;

Framework::Framework(sf::RenderWindow& window) :
	m_window(window),
	m_deltaTime(0),
	m_canObjectBePressed(false),
	m_canRMBBePressed(false),
	m_pDevTools(nullptr)
{
	m_pDataHandler = new DataHandler();
	m_pTextures = new Textures();
	m_pFonts = new Fonts();
	m_pAudio = new Audio();
	m_pMenu = new Menu(window, *m_pTextures, *m_pFonts, *m_pAudio);
	m_pGameSetUpScreen = new GameSetUpScreen(window, *m_pTextures, *m_pFonts, *m_pAudio, *m_pDataHandler);
	m_pGame = new Game(window, *m_pTextures, *m_pFonts, *m_pAudio, *m_pDataHandler, *m_pGameSetUpScreen, m_mouse);

	m_window.setFramerateLimit(144);
	m_window.setKeyRepeatEnabled(false);
	m_pDataHandler->loadData();
	m_pMenu->setInitializeDevTools(std::bind(&Framework::initializeDevTools, this));
	m_pGameSetUpScreen->initialize();
	m_pGame->initialize();

	m_pBackground = new UIElement(m_window, *m_pTextures);

	m_pBackground->setPosition(m_window.getDefaultView().getCenter());
	m_pBackground->setUpUIBorder(m_window.getSize().x - c_UIBorder, m_window.getSize().y - c_UIBorder);
	m_logo.setTexture(m_pTextures->m_logo);
	m_logo.setScale(0.6f, 0.6f);
	m_logo.setOrigin(m_logo.getLocalBounds().width * 0.5f, 0);
	m_logo.setPosition(m_window.getDefaultView().getCenter().x, 10);

	m_pAudio->playMusic(MusicEnum::menuMusic, 0);
}

Framework::~Framework()
{
	safeDelete(m_pDataHandler);
	safeDelete(m_pTextures);
	safeDelete(m_pFonts);
	safeDelete(m_pAudio);
	safeDelete(m_pMenu);
	if (m_pDevTools != nullptr) { safeDelete(m_pDevTools); }
	safeDelete(m_pGameSetUpScreen);
	safeDelete(m_pGame);
}

void Framework::run()
{
	while (m_window.isOpen())
	{
		//DeltaTime
		m_deltaTime = m_clock.restart().asSeconds();

		//FPS
		static int FPS = 0;
		FPS = static_cast<int> (1 / m_deltaTime);
		m_window.setTitle(std::to_string(FPS));

		mouseControl();

		checkWindowEvents();
		m_window.clear();

		switch (Global::g_gameState)
		{
		case GameState::menu:
		{
			menu();
		}
		break;

		case GameState::gameSetUpScreen:
		{
			gameSetUpScreen();
		}
		break;

		case GameState::game:
		{
			game();
		}
		break;

		case GameState::devTools:
		{
			devTools();
		}
		break;
		}

		m_window.display();
	}
}

void Framework::initializeDevTools()
{
	m_pDevTools = new DevTools(m_window, *m_pTextures, *m_pFonts, *m_pAudio, *m_pDataHandler, m_mouse);
	m_pDevTools->setFunctionToDeleteDevTools(std::bind(&Framework::deleteDevTools, this));
	m_pDevTools->initialize();
}

void Framework::deleteDevTools()
{
	safeDelete(m_pDevTools);
}

void Framework::checkWindowEvents()
{
	while (m_window.pollEvent(Global::g_event))
	{
		if (Global::g_event.type == sf::Event::GainedFocus)
		{
			Global::g_isWindowFocused = true;
		}
		else if (Global::g_event.type == sf::Event::LostFocus)
		{
			Global::g_isWindowFocused = false;
		}

		if (Global::g_event.type == sf::Event::Closed)
		{
			m_window.close();
		}

		// catch the resize events
		if (Global::g_event.type == sf::Event::Resized)
		{
			// update the view to the new size of the window
			sf::FloatRect visibleArea(0.0f, 0.0f, Global::g_event.size.width, Global::g_event.size.height);
			m_window.setView(sf::View(visibleArea));
		}
	}
}

void Framework::menu()
{
	m_pBackground->drawUIBackground();
	m_pMenu->update(m_mousePosition);
	m_pMenu->draw();
	m_window.draw(m_logo);
	m_pBackground->drawUIBorder();
}

void Framework::gameSetUpScreen()
{
	m_pBackground->drawUIBackground();
	m_pGameSetUpScreen->update(m_mousePosition);
	m_pGameSetUpScreen->draw();
	m_window.draw(m_logo);
	m_pBackground->drawUIBorder();
}

void Framework::devTools()
{
	m_pBackground->drawUIBorderAndBackground();
	m_pDevTools->update(m_mousePosition, m_deltaTime);
}

void Framework::game()
{
	m_pGame->update(m_mousePosition, m_deltaTime);
	m_pGame->draw();
}

void Framework::mouseControl()
{
	//LMB
	if (Global::g_wasObjectPressed)
	{
		Global::g_isLMBPressed = !Global::g_isLMBPressed;
		m_canObjectBePressed = !m_canObjectBePressed;
		Global::g_wasObjectPressed = false;
	}

	if (!m_mouse.isButtonPressed(sf::Mouse::Button::Left))
	{
		m_canObjectBePressed = true;
	}

	Global::g_isLMBPressed = (m_canObjectBePressed && m_mouse.isButtonPressed(sf::Mouse::Button::Left) && Global::g_isWindowFocused);

	//RMB

	if (Global::g_wasRMBPressed)
	{
		Global::g_isRMBPressed = !Global::g_isRMBPressed;
		m_canRMBBePressed = !m_canRMBBePressed;
		Global::g_wasRMBPressed = false;
	}

	if (!m_mouse.isButtonPressed(sf::Mouse::Button::Right))
	{
		m_canRMBBePressed = true;
	}

	Global::g_isRMBPressed = (m_canRMBBePressed && m_mouse.isButtonPressed(sf::Mouse::Button::Right) && Global::g_isWindowFocused);

	//Update mouse position
	m_mousePosition = m_window.mapPixelToCoords(m_mouse.getPosition(m_window));
}
