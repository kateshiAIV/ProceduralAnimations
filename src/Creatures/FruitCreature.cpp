#include <SFML/Graphics.hpp>
#include "FruitCreature.h"
#include <iostream>

FruitCreature::FruitCreature(float x, float y, CreatureType creatureType) : Creature(x, y, creatureType)
{

}

void FruitCreature::update(float time, std::vector<std::unique_ptr<Creature>>& creatures)
{
    Creature::update(time, creatures);

    sf::Vector2f fruitPos = m_Body[0].getPosition();
    float fruitR = m_Body[0].getRadius();



    for (size_t i = 0; i < creatures.size(); ++i)
    {
        Creature* c = creatures[i].get();

        if (c == this) continue; 
        if (c->getCreatureType() != CreatureType::Vegan) continue;

        sf::Vector2f veganPos = c->m_Body[0].getPosition();
        float veganR = c->m_Body[0].getRadius();

        float dx = fruitPos.x - veganPos.x;
        float dy = fruitPos.y - veganPos.y;
        float distance = std::sqrt(dx * dx + dy * dy);

        if (distance < fruitR + veganR)
        {
            setIsDead(true);
            c->setIsFed(true);
        }
    }
}
