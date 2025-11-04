#include <SFML/Graphics.hpp>
#include "Segment.h"
#include "Creature.h"



int main()
{

	Creature creature;
    auto window = sf::RenderWindow(sf::VideoMode({1920u, 1080u}), "CMake SFML Project");
    window.setFramerateLimit(144);
	sf::Clock clock;

    while (window.isOpen())
    {

        // Process events
        while (const auto event = window.pollEvent())
        {
            // Close window: exit
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }

            // Escape pressed: exit
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                keyPressed && keyPressed->code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }

            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                creature.setDesiredPosition(sf::Vector2f(static_cast<float>(mouseMoved->position.x), static_cast<float>(mouseMoved->position.y)));
            }
        }

        float time = clock.getElapsedTime().asSeconds();
		creature.update(time);
        window.clear();
        creature.draw(window);
        window.display();
    }
}
