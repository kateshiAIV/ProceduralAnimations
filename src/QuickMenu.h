#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class QuickMenu
{
private:
    sf::Vector2f position;
    std::vector<sf::RectangleShape> buttons;
    std::vector<sf::Text> labels;
    sf::Font font;
    bool visible = false;

public:
    QuickMenu();
    void setPosition(const sf::Vector2f& pos);
    void draw(sf::RenderWindow& window) const;
    bool handleClick(const sf::Vector2f& mousePos);
    void show();
    void hide();
    bool isVisible() const;
};
