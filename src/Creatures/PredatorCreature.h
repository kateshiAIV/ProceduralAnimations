#pragma once


#include <vector>
#include "Segment.h"
#include "Creature.h"
#include <SFML/Graphics.hpp>


class PredatorCreature : private Creature
{
public:
	PredatorCreature(float x, float y, float clr, CreatureType creatureType);
};