#pragma once


#include <vector>
#include "Segment.h"
#include <SFML/Graphics.hpp>

class Creature
{
private:
	std::array<Segment, 8> m_Body;
public:
	Creature();
	void draw(sf::RenderWindow& window) const;
};