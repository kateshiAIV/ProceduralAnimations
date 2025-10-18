#include <SFML/Graphics.hpp>
#include "Segment.h"
#include <cmath>
#include <array>

Segment::Segment(const sf::Vector2f& position, float angle, float distance, float radius, const sf::Color& color)
{
    m_Position = position;
    m_Angle = angle;
    m_Distance = distance;
    m_Radius = radius;
    m_Color = color;
	m_DesiredPosition = position;


    m_CircleShape.setRadius(m_Radius);
    m_CircleShape.setFillColor(m_Color);
    m_CircleShape.setOrigin(sf::Vector2f(m_Radius, m_Radius)); 
    m_CircleShape.setPosition(m_Position);


    float radianAngle = m_Angle * 3.14159265f / 180.0f;
    sf::Vector2f dir(std::cos(radianAngle), std::sin(radianAngle));

    point1 = m_Position;                  
    point2 = m_Position + dir * m_Radius; 
}

sf::Vector2f Segment::getEndPosition() const
{
    float radianAngle = m_Angle * 3.14159265f / 180.0f;
    return sf::Vector2f(
        m_Position.x + m_Distance * std::cos(radianAngle),
        m_Position.y + m_Distance * std::sin(radianAngle)
    );
}

void Segment::draw(sf::RenderWindow& window) const
{
    std::array<sf::Vertex, 2> line = {
        sf::Vertex({point1}),
        sf::Vertex({point2})
    };
    sf::CircleShape arrow(3.f);
    arrow.setFillColor(sf::Color::Red);
    arrow.setOrigin(sf::Vector2f(3.f, 3.f));
    arrow.setPosition(point2);
    window.draw(m_CircleShape);
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    window.draw(arrow);
}

void Segment::addOffsetRotation(float offset)
{
    m_Angle += offset;
    if (m_Angle >= 360.f)
        m_Angle -= 360.f;
    else if (m_Angle < 0.f)
        m_Angle += 360.f;
    float radianAngle = m_Angle * 3.14159265f / 180.0f;
    sf::Vector2f dir(std::cos(radianAngle), std::sin(radianAngle));

    point1 = m_Position;
    point2 = m_Position + dir * m_Radius;
}

sf::Vector2f Segment::getPosition() const
{
    return m_Position;
}

void Segment::setPosition(const sf::Vector2f& position)
{
    m_Position = position;
	m_CircleShape.setPosition(m_Position);
}

void Segment::setDesiredPosition(const sf::Vector2f& desiredPosition)
{
    m_DesiredPosition = desiredPosition;
}

float Segment::getRadius() const
{
    return m_Radius;
}


void Segment::update()
{
    // Compute direction vector from current position to desired target
    sf::Vector2f direction = m_DesiredPosition - m_Position;

    // Compute angle (in degrees)
    m_Angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;

    // Update segment end based on new facing angle
    float radianAngle = m_Angle * 3.14159265f / 180.0f;
    sf::Vector2f dir(std::cos(radianAngle), std::sin(radianAngle));

    point1 = m_Position;
    point2 = m_Position + dir * m_Radius;

	m_Position = m_Position + direction * 0.075f;
	m_CircleShape.setPosition(m_Position);
}
