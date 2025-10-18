#include <SFML/Graphics.hpp>
#include "Creature.h"


Creature::Creature()
    : m_Body{
        Segment({0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, sf::Color::White),
        Segment({0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, sf::Color::White),
        Segment({0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, sf::Color::White),
        Segment({0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, sf::Color::White),
        Segment({0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, sf::Color::White),
        Segment({0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, sf::Color::White),
        Segment({0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, sf::Color::White),
        Segment({0.0f, 0.0f}, 0.0f, 0.0f, 0.0f, sf::Color::White)
    }
{
    float r1 = 50.0f;
    sf::Vector2f startPos = { 960.f, 540.f }; 

    for (int i = 0; i < 8; i++)
    {
        float r = r1 - i * (r1 / (8 - 1)); 
        float distance = 50.f + i * 20.f;  

        sf::Vector2f pos;
        if (i == 0)
        {
            pos = startPos;
        }
        else
        {
            pos = m_Body[i - 1].getPosition() - sf::Vector2f(m_Body[i - 1].getRadius(), 0.f);
        }

        m_Body[i] = Segment(pos, 0.0f, distance, r, sf::Color(255 - i * 30, i * 30, 150));
    }

}


void Creature::draw(sf::RenderWindow& window) const
{
    for (const auto& segment : m_Body)
    {
        segment.draw(window);
    }
}