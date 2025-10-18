

#include <SFML/Graphics.hpp>
#include "Segment.h"




Segment::Segment(const sf::Vector2f& position, float angle, float distance, float radius, const sf::Color& color)
{
	m_Angle = angle;
	m_Position = position;
	m_Distance = distance;
	m_Radius = radius;
	m_Color = color;

}



sf::Vector2f Segment::getEndPosition() const
{
    float radianAngle = m_Angle * 3.14159265f / 180.0f;
    return sf::Vector2f(
        m_Position.x + m_Distance * cos(radianAngle),
        m_Position.y + m_Distance * sin(radianAngle)
    );
}


void Segment::draw(sf::RenderWindow& window) const
{
    sf::CircleShape circle(m_Radius);
    circle.setFillColor(m_Color);
    circle.setOrigin(sf::Vector2f(m_Radius, m_Radius)); // center origin
    circle.setPosition(m_Position);

    float radianAngle = m_Angle * 3.14159265f / 180.0f;
    sf::Vector2f dir(std::cos(radianAngle), std::sin(radianAngle));


    sf::Vector2f p1 = m_Position; // start point
    sf::Vector2f p2 = m_Position + dir * m_Radius; // end point

    std::array<sf::Vertex, 2> line = {
        sf::Vertex({p1}),
        sf::Vertex({p2})
    };

    sf::CircleShape arrow(3.f);
    arrow.setFillColor(sf::Color::Red);
    arrow.setOrigin(sf::Vector2f(3.f, 3.f));
    arrow.setPosition(p2);


    window.draw(circle);
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    window.draw(arrow);
}



void Segment::addOffsetRotation(float offset)
{
    m_Angle += offset;
    if (m_Angle >= 360.f)
		m_Angle -= 360.f;
}


sf::Vector2f  Segment::getPosition() const { return m_Position; }
float Segment::getRadius() const { return m_Radius; }