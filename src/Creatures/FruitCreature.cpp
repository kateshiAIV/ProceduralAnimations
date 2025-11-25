#include <SFML/Graphics.hpp>
#include "FruitCreature.h"
#include <iostream>

FruitCreature::FruitCreature(float x, float y, CreatureType creatureType) : Creature(x, y, creatureType)
{

}

void FruitCreature::update(float time, std::vector<std::unique_ptr<Creature>>& creatures)
{

	Creature::update(time, creatures);

	std::cout << "123" << std::endl;
}