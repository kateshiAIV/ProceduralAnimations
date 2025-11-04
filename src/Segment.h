#pragma once


#include <SFML/Graphics.hpp>

class Segment
{

private:
    sf::Vector2f m_Position;
    sf::Vector2f m_DesiredPosition;
    float m_Angle;
    float m_Distance;
    float m_Radius;
    sf::Color m_Color;
	sf::CircleShape m_CircleShape;
    sf::Vector2f point1 = m_Position; 
    sf::Vector2f point2 = m_Position; 
    sf::Vector2f helppoint0 = m_Position;
    sf::Vector2f helppoint1 = m_Position;
	sf::Vector2f ChildDesiredPosition = m_Position;
    sf::ConvexShape convex;
    


public:
	Segment() = default;
    Segment(const sf::Vector2f& position, float angle, float distance, float radius, const sf::Color& color);
    void draw(sf::RenderWindow& window) const;
    sf::Vector2f  getPosition() const;
	void setPosition(const sf::Vector2f& position);
	void setDesiredPosition(const sf::Vector2f& desiredPosition);
	float getRadius() const;
	void update(Segment parentSegment, float time);
    sf::Vector2f getHelpPoint0();
    sf::Vector2f getHelpPoint1();
    sf::Vector2f getChildDesiredPosition();
};