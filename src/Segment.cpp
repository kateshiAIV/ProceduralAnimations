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


    //window.draw(line.data(), line.size(), sf::PrimitiveType::Lines);
    
    //window.draw(helpline0.data(), line.size(), sf::PrimitiveType::Lines);
    //window.draw(helpline1.data(), line.size(), sf::PrimitiveType::Lines);
    //window.draw(arrow);
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


void Segment::updateHead(Segment parentSegment, float time)
{
    // Compute direction vector from current position to desired target
    sf::Vector2f direction = point2 - m_Position;
    sf::Vector2f direction1 = m_DesiredPosition - m_Position;
    float distance = std::hypot(m_DesiredPosition.x - m_Position.x,
        m_DesiredPosition.y - m_Position.y);


    // Compute angle (in degrees)
    float m_DesiredAngle = std::atan2(direction1.y, direction1.x) * 180.f / 3.14159265f;

    // Normalize both angles to [0, 360)
    auto normalizeAngle = [](float angle) {
        while (angle < 0) angle += 360.f;
        while (angle >= 360.f) angle -= 360.f;
        return angle;
        };

    m_Angle = normalizeAngle(m_Angle);
    m_DesiredAngle = normalizeAngle(m_DesiredAngle);

    // Compute smallest angular difference
    float diff = m_DesiredAngle - m_Angle;
    if (diff > 180.f) diff -= 360.f;
    if (diff < -180.f) diff += 360.f;

    // Smoothly rotate toward target angle
    float rotationSpeed = 0.5f; // degrees per second
    float maxStep = rotationSpeed; // frame time delta
    if (std::abs(diff) < maxStep)
        m_Angle = m_DesiredAngle;
    else
        m_Angle += (diff > 0 ? 1 : -1) * maxStep;

    // Update segment end based on new facing angle
    float radianAngle = m_Angle * 3.14159265f / 180.0f;
    sf::Vector2f dir(std::cos(radianAngle), std::sin(radianAngle));

    // 
    float waveAmplitude = 60.0f;
    float waveFrequency = 9.0f;
    float offset = std::clamp(std::cos(time * waveFrequency),-1.0f,1.0f) * waveAmplitude;


    sf::Vector2f perpendicular(-dir.y, dir.x);
    //m_Position = m_Position + direction * 0.075f;
    float clampedX = std::clamp(direction.x, -90.0f, 90.0f);
    float clampedY = std::clamp(direction.y, -90.0f, 90.0f);
    m_Position = m_Position + sf::Vector2f(clampedX, clampedY)  /*direction*/ * 0.055f + perpendicular * offset * 0.055f;
    

    point1 = m_Position;
    point2 = m_Position + dir * m_Radius;

    radianAngle = (m_Angle + 90) * 3.14159265f / 180.0f;
    sf::Vector2f helpdir0(std::cos(radianAngle), std::sin(radianAngle));
    helppoint0 = m_Position + helpdir0 * (m_Radius - 10.0f);

    radianAngle = (m_Angle - 90) * 3.14159265f / 180.0f;
    sf::Vector2f helpdir1(std::cos(radianAngle), std::sin(radianAngle));
    helppoint1 = m_Position + helpdir1 * (m_Radius - 10.0f);

    radianAngle = (m_Angle - 180) * 3.14159265f / 180.0f;
    sf::Vector2f helpDirChild(std::cos(radianAngle), std::sin(radianAngle));
    ChildDesiredPosition = m_Position + helpDirChild * m_Radius;

    m_CircleShape.setPosition(m_Position);

    convex.setPoint(0, helppoint0);
    convex.setPoint(1, helppoint1);
    convex.setPoint(2, parentSegment.getHelpPoint1());
    convex.setPoint(3, parentSegment.getHelpPoint0());
    convex.setFillColor(m_Color);
}


void Segment::updateBody(Segment parentSegment, float time)
{
    // Compute direction vector from current position to desired target
    sf::Vector2f direction = m_DesiredPosition - m_Position;
    float distance = std::hypot(m_DesiredPosition.x - m_Position.x,
        m_DesiredPosition.y - m_Position.y);


    // Compute angle (in degrees)
    m_Angle = std::atan2(direction.y, direction.x) * 180.f / 3.14159265f;

    // Update segment end based on new facing angle
    float radianAngle = m_Angle * 3.14159265f / 180.0f;
    sf::Vector2f dir(std::cos(radianAngle), std::sin(radianAngle));

    // 
    float waveAmplitude = distance / 2.0f;
    float waveFrequency = distance / 10.0f;
    float offset = std::clamp(std::cos(time * waveFrequency), -1.0f, 1.0f) * waveAmplitude;


    sf::Vector2f perpendicular(-dir.y, dir.x);
    //m_Position = m_Position + direction * 0.075f;
    if (distance>= 3) {
        m_Position = m_Position + direction * 0.075f;
    }

    point1 = m_Position;
    point2 = m_Position + dir * m_Radius;

    radianAngle = (m_Angle + 90) * 3.14159265f / 180.0f;
    sf::Vector2f helpdir0(std::cos(radianAngle), std::sin(radianAngle));
    helppoint0 = m_Position + helpdir0 * (m_Radius - 15.0f);

    radianAngle = (m_Angle - 90) * 3.14159265f / 180.0f;
    sf::Vector2f helpdir1(std::cos(radianAngle), std::sin(radianAngle));
    helppoint1 = m_Position + helpdir1 * (m_Radius - 15.0f);

    radianAngle = (m_Angle - 180) * 3.14159265f / 180.0f;
    sf::Vector2f helpDirChild(std::cos(radianAngle), std::sin(radianAngle));
    ChildDesiredPosition = m_Position + helpDirChild * m_Radius;

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

sf::Vector2f Segment::getChildDesiredPosition()
{
    return ChildDesiredPosition;
}