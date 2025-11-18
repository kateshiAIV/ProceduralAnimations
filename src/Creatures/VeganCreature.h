#pragma once


#include <vector>
#include "Segment.h"
#include "Creature.h"
#include <SFML/Graphics.hpp>


class VeganCreature : private Creature
{
	VeganCreature(float x, float y, float clr, CreatureType creatureType);
};