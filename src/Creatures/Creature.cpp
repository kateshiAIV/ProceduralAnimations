#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include "Creature.h"


struct CreatureConfig
{
    float color;
	float radius;
    int size;
    float waveAmplitude;
    float waveFrequency;
    float maxHeadSpeed;
};

std::map<CreatureType, CreatureConfig> CreatureSettings = {
    {
        CreatureType::Predator,
        CreatureConfig{ 255,45.0f, 8,60.0f, 9.0f, 90.0f }
    },
    {
        CreatureType::Vegan,
        CreatureConfig{ 115,20.0f, 4, 25.0f, 12.0f, 90.0f }
    },
    {
        CreatureType::Fruit,
        CreatureConfig{ 60 , 10.0f, 1, 15.0f, 15.0f, 90.0f }
    }
};


Creature::Creature(float x, float y, CreatureType creatureType)
{   

    m_CreatureType = creatureType;
	auto& config = CreatureSettings[creatureType];
    float r1 = config.radius;
    sf::Vector2f startPos = { 960.f, 540.f }; 

    for (int i = 0; i < config.size; i++)
    {
        float r = r1 - i * (r1 / (config.size)); 
        float distance = 50.f + i * 20.f;  
        sf::Vector2f pos;
        if (i == 0)
        {
            pos = sf::Vector2f(x, y);
            m_Body.push_back(Segment(pos, 0.0f, distance,r,sf::Color(config.color - i * 30, i * 30, 150), config.waveAmplitude, config.waveFrequency,config.maxHeadSpeed));

        }
        else
        {
            pos = m_Body[i - 1].getPosition() - sf::Vector2f(m_Body[i - 1].getRadius(), 0.f);
            m_Body.push_back(Segment(pos, 0.0f, distance, r, sf::Color(config.color - i * 30, i * 30, 150), config.waveAmplitude, config.waveFrequency, config.maxHeadSpeed));
        }
    }

}


void Creature::draw(sf::RenderWindow& window) const
{
    for (const auto& segment : m_Body)
    {
        segment.draw(window);
    }
}


void Creature::setDesiredPosition(const sf::Vector2f& desiredPosition)
{
    m_DesiredPosition = desiredPosition;
}


void Creature::update(float time, std::vector<std::unique_ptr<Creature>>& creatures)
{
    if (m_Body.empty()) { return; };

    m_Body[0].setDesiredPosition(m_DesiredPosition);
    m_Body[0].updateHead(m_Body[0], time);


    for (auto& c : creatures)
{
    switch (m_CreatureType)
    {
    case CreatureType::Predator:
    {
        if (c->getCreatureType() == CreatureType::Vegan)
        {
            setDesiredPosition(c->m_Body[0].getPosition());
        }
        break;
    }
    case CreatureType::Vegan:
    {
        if (c->getCreatureType() == CreatureType::Fruit)
        {
            setDesiredPosition(c->m_Body[0].getPosition());
        }
        if (c->getCreatureType() == CreatureType::Predator)
        {
            //toDo
            //delete vegan 
        }
        break;
    }
    }
}

    for (size_t i = 1; i < m_Body.size(); ++i)
    {
        m_Body[i].setDesiredPosition(m_Body[i - 1].getChildDesiredPosition());
        m_Body[i].updateBody(m_Body[i-1], time);
    }
}

//for (auto& c : creatures)
//{
//    switch (m_CreatureType)
//    {
//    case CreatureType::Predator:
//    {
//        if (c->getCreatureType() == CreatureType::Vegan)
//        {
//            setDesiredPosition(c->m_Body[0].getPosition());
//        }
//        break;
//    }
//    case CreatureType::Vegan:
//    {
//        if (c->getCreatureType() == CreatureType::Fruit)
//        {
//            setDesiredPosition(c->m_Body[0].getPosition());
//        }
//        if (c->getCreatureType() == CreatureType::Predator)
//        {
//            //toDo
//            //delete vegan 
//        }
//        break;
//    }
//    case CreatureType::Fruit:
//    {
//        //toDo
//        //delete Fruit
//        break;
//    }
//    }
//}



CreatureType Creature::getCreatureType() 
{
    return m_CreatureType;
}


bool Creature::getIsDead()
{
    return bIsDead;
}


void Creature::setIsDead(bool isDead)
{
    bIsDead = isDead;
}