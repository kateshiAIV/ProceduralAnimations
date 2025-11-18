#pragma once


#include <vector>
#include "Segment.h"
#include "Creature.h"
#include <SFML/Graphics.hpp>


class FruitCreature : private Creature
{
public:
	FruitCreature(float x, float y, float clr, CreatureType creatureType);
};