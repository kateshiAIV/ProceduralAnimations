#include <SFML/Graphics.hpp>
#include "Creature.h"


Creature::Creature()
    : m_Body{
        Segment(),
        Segment(),
        Segment(),
        Segment(),
        Segment(),
        Segment(),
        Segment(),
        Segment()
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


void Creature::setDesiredPosition(const sf::Vector2f& desiredPosition)
{
    m_DesiredPosition = desiredPosition;
}


void Creature::update(float time)
{
    if (m_Body.empty()) { return; };

    m_Body[0].setDesiredPosition(m_DesiredPosition);
    m_Body[0].update(m_Body[0], time);

    for (size_t i = 1; i < m_Body.size(); ++i)
    {
        m_Body[i].setDesiredPosition(m_Body[i - 1].getChildDesiredPosition());
        m_Body[i].update(m_Body[i-1], time);
    }
}