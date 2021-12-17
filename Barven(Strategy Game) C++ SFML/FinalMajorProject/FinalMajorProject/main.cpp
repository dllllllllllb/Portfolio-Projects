#include <SFML/Window/ContextSettings.hpp>
#include "framework.h"
#include "vld.h"


int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 16;
    sf::RenderWindow window(sf::VideoMode(1920, 1080), "Barven", sf::Style::Default, settings);

    Framework m_game(window);
    m_game.run();

    return 0;
}