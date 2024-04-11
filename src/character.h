#ifndef Character_H
#define Character_H

#include "constants.h"
#include <string>
#include <iostream>

class Character
{
public:
    int characterId;
    float x_position;
    float y_position;

    std::string characterName;
    

    Character(int characterId);
    void setPosition(float x_position, float y_position);
};

#endif // Character_H
