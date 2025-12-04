#include <SFML/Graphics.hpp>
#include "VeganCreature.h"
#include <iostream>


VeganCreature::VeganCreature(float x, float y, CreatureType creatureType) : Creature(x,y, creatureType)
{
    
}


void VeganCreature::update(float time, std::vector<std::unique_ptr<Creature>>& creatures)
{
    Creature::update(time, creatures);

    sf::Vector2f veganPos = m_Body[0].getPosition();
    float veganR = m_Body[0].getRadius();

    for (size_t i = 0; i < creatures.size(); ++i)
    {
        Creature* c = creatures[i].get();
        if (c == this) continue;
        sf::Vector2f otherCreaturePos = c->m_Body[0].getPosition();
        float otherCreatureR = c->m_Body[0].getRadius();
        float dx = veganPos.x - otherCreaturePos.x;
        float dy = veganPos.y - otherCreaturePos.y;
        float distance = std::sqrt(dx * dx + dy * dy);
        if (c->getCreatureType() == CreatureType::Vegan)
        {
            if (c->getIsFed() && getIsFed())
            {
                if (distance < veganR + otherCreatureR)
                {
                    setIsFed(false);
                    c->setIsFed(false);
                    creatures.push_back(std::make_unique<VeganCreature>(
                        this->m_Body[0].getPosition().x,
                        this->m_Body[0].getPosition().y,
                        CreatureType::Vegan
                    ));
                }
            }
        }
        if (c->getCreatureType() == CreatureType::Predator)
        {
            if (distance < veganR + otherCreatureR)
            {
                setIsDead(true);
                c->setIsFed(true);
            }
        }
        float minDistanceToPrey = 1000000.0f;
        if (getIsFed())
        {
            if ((c->getCreatureType() == CreatureType::Vegan) && (c->getIsFed()))
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
            if (c->getCreatureType() == CreatureType::Fruit)
            {
                float distanceToCreature = c->getDistanceTo(this);
                std::cout << distanceToCreature << std::endl;
                if (distanceToCreature < minDistanceToPrey)
                {
                    minDistanceToPrey = distanceToCreature;
                    setDesiredPosition(c->m_Body[0].getPosition());
                }
            }
        }

    }
}