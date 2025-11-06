#include <SFML/Graphics.hpp>
#include "Segment.h"
#include "Creature.h"
#include "QuickMenu.h"



int main()
{


    std::vector<Creature> creatures(10);


	Creature creature;
    auto window = sf::RenderWindow(sf::VideoMode({3840u, 2160u}), "CMake SFML Project");
    window.setFramerateLimit(144);
	sf::Clock clock;

    sf::View view = window.getDefaultView();
    view.zoom(1.0f); 
    window.setView(view);


    QuickMenu menu;

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

            // left mouse button pressed: creature menu
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    Creature creature;
					creatures.push_back(creature);


                    sf::Vector2f mousePos(
                        static_cast<float>(mousePressed->position.x),
                        static_cast<float>(mousePressed->position.y)
                    );

                    if (!menu.isVisible()) {
                        menu.setPosition(mousePos);
                        menu.show();
                    }
                    else {
                        if(menu.handleClick(mousePos)) continue;
                        menu.setPosition(mousePos);
                    }
                }
            }


            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {
                creature.setDesiredPosition(sf::Vector2f(static_cast<float>(mouseMoved->position.x), static_cast<float>(mouseMoved->position.y)));
                for (int i = 0; i < creatures.size(); i++)
                {
                    creatures[i].setDesiredPosition(sf::Vector2f(static_cast<float>(mouseMoved->position.x), static_cast<float>(mouseMoved->position.y)));
                }
            
            }
        }

        float time = clock.getElapsedTime().asSeconds();

        for (int i = 0; i < creatures.size(); i++)
        {
            creatures[i].update(time);
        }

		creature.update(time);
        window.clear();
        for (int i = 0; i < creatures.size(); i++)
        {
			creatures[i].draw(window);
        }

        creature.draw(window);
        menu.draw(window);
        window.display();
    }
}
