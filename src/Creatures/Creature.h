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
	CreatureType m_CreatureType;
public:
	std::vector<Segment> m_Body;
	virtual ~Creature() = default;
	Creature(float x, float y, CreatureType creatureType);
	void draw(sf::RenderWindow& window) const;
	void setDesiredPosition(const sf::Vector2f& desiredPosition);
	virtual void update(float time, std::vector<std::unique_ptr<Creature>>& creatures);
	CreatureType getCreatureType();

};