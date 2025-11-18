#include "QuickMenu.h"
#include "Creatures/Creature.h"
#include <iostream>

QuickMenu::QuickMenu()
{
    font.openFromFile("times.ttf"); 

    std::vector<std::string> options = { "predator", "vegan", "fruit", "close" };

    float width = 160.f;
    float height = 40.f;
    float spacing = 5.f;

    for (size_t i = 0; i < options.size(); ++i)
    {
        sf::RectangleShape rect({ width, height });
        rect.setFillColor(sf::Color(70, 70, 70, 230));
        rect.setOutlineColor(sf::Color::White);
        rect.setOutlineThickness(1.f);
        buttons.push_back(rect);

        sf::Text text(font, "", 30);
        text.setFont(font);
        text.setString(options[i]);
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);
        labels.push_back(text);
    }
}

void QuickMenu::setPosition(const sf::Vector2f& pos)
{
    position = pos;
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        buttons[i].setPosition(sf::Vector2f(pos.x, pos.y + i * 45.f));
        labels[i].setPosition(sf::Vector2f(pos.x + 10.f, pos.y + i * 45.f + 8.f));
    }
}

void QuickMenu::draw(sf::RenderWindow& window) const
{
    if (!visible) return;
    for (size_t i = 0; i < buttons.size(); ++i)
    {
        window.draw(buttons[i]);
        window.draw(labels[i]);
    }
}

CreatureType QuickMenu::handleClick(const sf::Vector2f& mousePos)
{
    if (!visible) return CreatureType::None;

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (buttons[i].getGlobalBounds().contains(mousePos))
        {
            std::string option = labels[i].getString();
            std::cout << "Selected: " << option << std::endl;

            if (option == "close")
            {
                return CreatureType::None;
            }
            else if (option == "predator")
            {
                return CreatureType::Predator;
            }
            else if (option == "vegan")
            {
                return CreatureType::Vegan;
            }
            else if (option == "fruit")
            {
                return CreatureType::Fruit;
            }
        }
    }
	return CreatureType::None;
}

void QuickMenu::show()
{
    visible = true;
}

void QuickMenu::hide()
{
    visible = false;
}

bool QuickMenu::isVisible() const
{
    return visible;
}
