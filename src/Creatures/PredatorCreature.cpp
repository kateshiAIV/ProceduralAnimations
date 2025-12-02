#include <SFML/Graphics.hpp>
#include "PredatorCreature.h"


PredatorCreature::PredatorCreature(float x, float y, CreatureType creatureType) : Creature(x, y, creatureType)
{}


void PredatorCreature::update(float time, std::vector<std::unique_ptr<Creature>>& creatures)
{
	Creature::update(time, creatures);

	float minDistanceToPrey = 10000000.0f;

	for (auto& c : creatures)
	{
		if (c->getCreatureType() == CreatureType::Vegan)
		{
			float distance = c->getDistanceTo(this);
			if (distance < minDistanceToPrey)
			{
				minDistanceToPrey = distance;
				setDesiredPosition(c->m_Body[0].getPosition());
			}
		}
	}

}

