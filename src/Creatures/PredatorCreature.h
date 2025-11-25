#pragma once


#include <vector>
#include "Segment.h"
#include "Creature.h"
#include <SFML/Graphics.hpp>


class PredatorCreature : public Creature
{
public:
	PredatorCreature(float x, float y, CreatureType creatureType);
};