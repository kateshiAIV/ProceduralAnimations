#pragma once


#include <SFML/Graphics.hpp>

class Segment
{

private:
    sf::Vector2f m_Position;
    float m_Angle;
    float m_Distance;
    float m_Radius;
    sf::Color m_Color;


public:

    Segment(const sf::Vector2f& position, float angle, float distance, float radius, const sf::Color& color);
    sf::Vector2f getEndPosition() const;
    void draw(sf::RenderWindow& window) const;
    void addOffsetRotation(float offset);
    sf::Vector2f  getPosition() const;
	float getRadius() const;

};