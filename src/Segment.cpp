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

    convex.setPointCount(4);
    convex.setPoint(0, sf::Vector2f(0.0f, 0.0f));
    convex.setPoint(1, sf::Vector2f(0.0f, 0.0f));
    convex.setPoint(2, sf::Vector2f(0.0f, 0.0f));
    convex.setPoint(3, sf::Vector2f(0.0f, 0.0f));
}


void Segment::draw(sf::RenderWindow& window) const
{
    std::array<sf::Vertex, 2> line = {
        sf::Vertex({point1}),
        sf::Vertex({point2})
    };

    std::array<sf::Vertex, 2> helpline0 = {
    sf::Vertex({point1}),
    sf::Vertex({helppoint0})
    };

    std::array<sf::Vertex, 2> helpline1 = {
    sf::Vertex({point1}),
    sf::Vertex({helppoint1})
    };



    sf::CircleShape arrow(3.f);
    arrow.setFillColor(sf::Color::Red);
    arrow.setOrigin(sf::Vector2f(3.f, 3.f));
    arrow.setPosition(point2);




    window.draw(m_CircleShape);
    window.draw(convex);
    window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    window.draw(helpline0.data(), line.size(), sf::PrimitiveType::Lines);
    window.draw(helpline1.data(), line.size(), sf::PrimitiveType::Lines);
    window.draw(arrow);
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


void Segment::update(Segment parentSegment)
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

    radianAngle = (m_Angle+90) * 3.14159265f / 180.0f;
    sf::Vector2f helpdir0(std::cos(radianAngle), std::sin(radianAngle));
    helppoint0 = m_Position + helpdir0 * (m_Radius - 5.0f);


    radianAngle = (m_Angle - 90) * 3.14159265f / 180.0f;
    sf::Vector2f helpdir1(std::cos(radianAngle), std::sin(radianAngle));
    helppoint1 = m_Position + helpdir1 * (m_Radius-5.0f);

	m_Position = m_Position + direction * 0.075f;
	m_CircleShape.setPosition(m_Position);

    convex.setPoint(0, helppoint0);
    convex.setPoint(1, helppoint1);
    convex.setPoint(2, parentSegment.getHelpPoint1());
    convex.setPoint(3, parentSegment.getHelpPoint0());
    convex.setFillColor(m_Color);

}


sf::Vector2f Segment::getHelpPoint0()
{
    return helppoint0;
}

sf::Vector2f Segment::getHelpPoint1()
{
    return helppoint1;
}