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
#include <memory>
#include <vector>
#include <algorithm>

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 3840, 2160 }), "CMake SFML Project");
    window.setFramerateLimit(144);

    //Clocks
    sf::Clock clock;
    sf::Clock cameraClock;


	//Camera settings
    float viewScale = 4.0f;
    float viewSpeed = 1000.0f;
    sf::View view = window.getDefaultView();
    view.zoom(viewScale);
    window.setView(view);

	//Background music
    sf::SoundBuffer soundBuffer;
    soundBuffer.loadFromFile("space.mp3");
    sf::Sound sound(soundBuffer);
    sound.setLooping(true);
    sound.play();

	//menu and creatures
    QuickMenu menu;
    std::vector<std::unique_ptr<Creature>> creatures;

    while (window.isOpen())
    {
        float dt = cameraClock.restart().asSeconds();

        //EVENTS
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();

            if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
            {
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                    window.close();
            }

			//MENU AND CREATURE SPAWN
            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>())
            {
                if (mousePressed->button == sf::Mouse::Button::Left)
                {
                    sf::Vector2f mousePos = window.mapPixelToCoords(
                        sf::Vector2i(mousePressed->position.x, mousePressed->position.y)
                    );

                    if (!menu.isVisible())
                    {
                        menu.setPosition(sf::Vector2f(mousePos.x - 80.f, mousePos.y - 80.f));
                        menu.show();
                    }
                    else
                    {
                        CreatureType type = menu.handleClick(mousePos);
                        if (type == CreatureType::Predator)
                            creatures.push_back(std::make_unique<PredatorCreature>(mousePos.x, mousePos.y, type));
                        else if (type == CreatureType::Vegan)
                            creatures.push_back(std::make_unique<VeganCreature>(mousePos.x, mousePos.y, type));
                        else if (type == CreatureType::Fruit)
                            creatures.push_back(std::make_unique<FruitCreature>(mousePos.x, mousePos.y, type));

                        menu.setPosition(mousePos);
                        menu.hide();
                    }
                }
            }

            if (const auto* mouseWheelScrolled = event->getIf<sf::Event::MouseWheelScrolled>())
            {

                std::cout << "wheel movement: " << mouseWheelScrolled->delta << std::endl;
                if (mouseWheelScrolled->delta == 1)
                {
                    menu.hide();
                    float zoomFactor = 0.8f;

                    sf::Vector2i pixel = sf::Mouse::getPosition(window);
                    sf::Vector2f beforeZoom = window.mapPixelToCoords(pixel);

                    view.zoom(zoomFactor);
                    viewScale *= zoomFactor;

                    sf::Vector2f afterZoom = window.mapPixelToCoords(pixel);
                    view.move(beforeZoom - afterZoom);

                    menu.setScaling(viewScale);
                    menu.rebuild();
                    window.setView(view);
                }
				else if (mouseWheelScrolled->delta == -1)
                {
                    menu.hide();
                    float zoomFactor = 1.25f;

                    sf::Vector2i pixel = sf::Mouse::getPosition(window);
                    sf::Vector2f beforeZoom = window.mapPixelToCoords(pixel);

                    view.zoom(zoomFactor);
                    viewScale *= zoomFactor;

                    sf::Vector2f afterZoom = window.mapPixelToCoords(pixel);
                    view.move(beforeZoom - afterZoom);

                    menu.setScaling(viewScale);
                    menu.rebuild();
                    window.setView(view);
                }
            }


        }

        //CAMERA MOVE
        sf::Vector2f camMove(0.f, 0.f);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) camMove.x -= viewSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) camMove.x += viewSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) camMove.y -= viewSpeed * dt;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) camMove.y += viewSpeed * dt;
        view.move(camMove);

		// FRUIT FOLLOW MOUSE, TODO: AI
        sf::Vector2i mousePixel = sf::Mouse::getPosition(window);
        sf::Vector2f mouseWorld = window.mapPixelToCoords(mousePixel);

        for (auto& c : creatures)
        {
            if (c->getCreatureType() == CreatureType::Fruit)
            {
                c->setDesiredPosition(mouseWorld);
            }
        }

        window.setView(view);

        //UPDATE CREATURES 
        float time = clock.getElapsedTime().asSeconds();
        for (auto& c : creatures)
        {
            c->update(time, creatures);
        }

        //RENDER 
        window.clear();

        for (auto& c : creatures)
            if (c->getCreatureType() == CreatureType::Fruit) c->draw(window);
        for (auto& c : creatures)
            if (c->getCreatureType() == CreatureType::Vegan) c->draw(window);
        for (auto& c : creatures)
            if (c->getCreatureType() == CreatureType::Predator) c->draw(window);

        //REMOVE DEAD
        creatures.erase(
            std::remove_if(creatures.begin(), creatures.end(),
                [](auto& c) { return c->getIsDead(); }),
            creatures.end()
        );

        menu.draw(window);
        window.display();
    }
}
