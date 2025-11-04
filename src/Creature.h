#pragma once


#include <vector>
#include "Segment.h"
#include <SFML/Graphics.hpp>

class Creature
{
private:
	std::array<Segment, 8> m_Body;
	sf::Vector2f m_DesiredPosition;
public:
	Creature();
	void draw(sf::RenderWindow& window) const;
	void setDesiredPosition(const sf::Vector2f& desiredPosition);
	void update(float time);
};