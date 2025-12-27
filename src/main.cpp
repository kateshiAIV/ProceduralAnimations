#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Creatures/Segment.h"
#include "Creatures/Creature.h"
#include "Creatures/PredatorCreature.h"
#include "Creatures/VeganCreature.h"
#include "Creatures/FruitCreature.h"
#include "QuickMenu.h"
#include <iostream>
#include <fstream>
#include <sstream>


int main()
{


    float viewScale = 4.0f;

    sf::SoundBuffer soundBuffer;
    soundBuffer.loadFromFile("space.mp3");
    sf::Sound sound(soundBuffer);
	sound.play();
    sound.setLooping(true);



    std::vector<std::unique_ptr<Creature>> creatures;

    auto window = sf::RenderWindow(sf::VideoMode({3840u, 2160u}), "CMake SFML Project");
    window.setFramerateLimit(144);
	sf::Clock clock;

    sf::View view = window.getDefaultView();
    view.zoom(viewScale); 
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

            // Down pressed: scale up
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                keyPressed && keyPressed->code == sf::Keyboard::Key::Down)
            {
                menu.hide();
                float newViewScale = 1.25f;
                view.zoom(newViewScale);
                viewScale *= newViewScale;
                menu.setScaling(viewScale);
                menu.rebuild();
                window.setView(view);
            }


            // Up pressed: scale down
            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>();
                keyPressed && keyPressed->code == sf::Keyboard::Key::Up)
            {
                menu.hide();
                float newViewScale = 0.8f;
                view.zoom(newViewScale);
                viewScale *= newViewScale;
                menu.setScaling(viewScale);
                menu.rebuild();
                window.setView(view);
            }


            // left mouse button pressed: creature menu
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {

                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        sf::Vector2i(mousePressed->position.x, mousePressed->position.y)
                    );


                    if (!menu.isVisible()) {
                        menu.setPosition(sf::Vector2f(mousePos.x-80.0f, mousePos.y-80.0f));
                        menu.show();
                    }
                    else {
                        if (menu.handleClick(mousePos) == CreatureType::Predator)
                        {
                            creatures.push_back(std::make_unique<PredatorCreature>(
                                mousePos.x,
                                mousePos.y,
                                CreatureType::Predator
                            ));
                        }
                        else if (menu.handleClick(mousePos) == CreatureType::Vegan)
                        {
                            creatures.push_back(std::make_unique<VeganCreature>(
                                mousePos.x,
                                mousePos.y,
                                CreatureType::Vegan
                            ));
                        }
                        else if (menu.handleClick(mousePos) == CreatureType::Fruit)
                        {
                            creatures.push_back(std::make_unique<FruitCreature>(
                                mousePos.x,
                                mousePos.y,
                                CreatureType::Fruit
                            ));
                        }


                        menu.setPosition(mousePos);
                        menu.hide();
                    }
                }
            }


            if (const auto* mouseMoved = event->getIf<sf::Event::MouseMoved>())
            {

                for (auto& c : creatures)
                {
                    if (c->getCreatureType() == CreatureType::Fruit)
                    {
                        c->setDesiredPosition(sf::Vector2f(static_cast<float>(mouseMoved->position.x), static_cast<float>(mouseMoved->position.y)));
                    }
                }
            
            }
        }

        float time = clock.getElapsedTime().asSeconds();

		window.clear();
        for (auto& c : creatures)
        {

            //ToDo
            /*Exception thrown : read access violation.
                c._Mypair.** _Myval2** was 0xFFFFFFFFFFFFFFFF.*/
			c->update(time, creatures);
        }
        for (auto& c : creatures)
        {
            if(c->getCreatureType() == CreatureType::Fruit) c->draw(window);
        }
        for (auto& c : creatures)
        {
            if(c->getCreatureType() == CreatureType::Vegan) c->draw(window);
        }
        for (auto& c : creatures)
        {
            if(c->getCreatureType() == CreatureType::Predator) c->draw(window);
        }
        creatures.erase(
            std::remove_if(
                creatures.begin(),
                creatures.end(),
                [](auto& c) { return c->getIsDead(); }
            ),
            creatures.end()
        );
        
        menu.draw(window);
        window.display();
    }
}
