#include "character.h"

Character::Character(int characterId)
{
    std::cout << "Character Created" << std::endl;
    this->characterId = characterId;
}

void Character::setPosition(float x_position, float y_position)
{
    this->x_position = x_position;
    this->y_position = y_position;
}
