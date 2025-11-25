#pragma once


#include <vector>
#include "Segment.h"
#include "Creature.h"
#include <SFML/Graphics.hpp>


class FruitCreature : public Creature
{
public:
	FruitCreature(float x, float y, CreatureType creatureType);
	void update(float time, std::vector<std::unique_ptr<Creature>>& creatures) override;
};