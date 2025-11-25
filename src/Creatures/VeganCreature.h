#pragma once


#include <vector>
#include "Segment.h"
#include "Creature.h"
#include <SFML/Graphics.hpp>


class VeganCreature : public Creature
{
public:
	VeganCreature(float x, float y, CreatureType creatureType);
};