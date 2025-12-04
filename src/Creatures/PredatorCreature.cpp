#include <SFML/Graphics.hpp>
#include "PredatorCreature.h"


PredatorCreature::PredatorCreature(float x, float y, CreatureType creatureType) : Creature(x, y, creatureType)
{}


void PredatorCreature::update(float time, std::vector<std::unique_ptr<Creature>>& creatures)
{
	Creature::update(time, creatures);


    sf::Vector2f predatorPos = m_Body[0].getPosition();
    float predatorR = m_Body[0].getRadius();

	float minDistanceToPrey = 10000000.0f;

	for (int i =0; i< creatures.size();i++)
	{

        Creature* c = creatures[i].get();
        if (c == this) continue;
        sf::Vector2f otherCreaturePos = c->m_Body[0].getPosition();
        float otherCreatureR = c->m_Body[0].getRadius();
        float dx = predatorPos.x - otherCreaturePos.x;
        float dy = predatorPos.y - otherCreaturePos.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        if (c->getCreatureType() == CreatureType::Predator)
        {
            if (c->getIsFed() && getIsFed())
            {
                if (distance < predatorR + otherCreatureR)
                {
                    setIsFed(false);
                    c->setIsFed(false);
                    creatures.push_back(std::make_unique<PredatorCreature>(
                        this->m_Body[0].getPosition().x,
                        this->m_Body[0].getPosition().y,
                        CreatureType::Predator
                    ));
                }
            }
        }
        float minDistanceToPrey = 1000000.0f;
        if (getIsFed())
        {
            if ((c->getCreatureType() == CreatureType::Predator) && (c->getIsFed()))
            {
                float distanceToCreature = c->getDistanceTo(this);
                if (distanceToCreature < minDistanceToPrey)
                {
                    minDistanceToPrey = distanceToCreature;
                    setDesiredPosition(c->m_Body[0].getPosition());
                }

            }
        }
        else
        {
            if (c->getCreatureType() == CreatureType::Vegan)
            {
                float distanceToCreature = c->getDistanceTo(this);
                if (distanceToCreature < minDistanceToPrey)
                {
                    minDistanceToPrey = distanceToCreature;
                    setDesiredPosition(c->m_Body[0].getPosition());
                }
            }
        }

	}

}

