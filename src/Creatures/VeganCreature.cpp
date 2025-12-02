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
        if (c->getCreatureType() != CreatureType::Predator) continue;

        sf::Vector2f predatorPos = c->m_Body[0].getPosition();
        float predatorR = c->m_Body[0].getRadius();

        float dx = veganPos.x - predatorPos.x;
        float dy = veganPos.y - predatorPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < veganR + predatorR)
        {
            setIsDead(true);
        }
    }

    float minDistanceToPrey = 1000000.0f;

    for (size_t i = 0; i < creatures.size(); ++i)
    {

        Creature* c = creatures[i].get();
        if (c == this) continue;

        if (c->getCreatureType() == CreatureType::Predator)
        {
            float distance = c->getDistanceTo(this);
            std::cout << distance << std::endl;
        }




        if (getIsFed())
        {
            if ((c->getCreatureType() == CreatureType::Vegan) && (c->getIsFed())) 
            {
                setDesiredPosition(c->m_Body[0].getPosition());
                break;
            }
        }
        else 
        {
            if (c->getCreatureType() == CreatureType::Fruit)
            {
                float distance1 = c->getDistanceTo(this);
                std::cout << distance1 << std::endl;
                if (distance1 < minDistanceToPrey)
                {
                    minDistanceToPrey = distance1;
                    setDesiredPosition(c->m_Body[0].getPosition());
                }
            }
        }
    }


}