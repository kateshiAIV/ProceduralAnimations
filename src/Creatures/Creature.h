#pragma once


#include <vector>
#include "Segment.h"
#include <SFML/Graphics.hpp>

enum class CreatureType
{
	Predator,
	Vegan,
	Fruit,
	None
};

class Creature
{
private:
	sf::Vector2f m_DesiredPosition;
public:
	std::vector<Segment> m_Body;
	Creature(float x, float y, float clr, CreatureType creatureType);
	void draw(sf::RenderWindow& window) const;
	void setDesiredPosition(const sf::Vector2f& desiredPosition);
	void update(float time);
};