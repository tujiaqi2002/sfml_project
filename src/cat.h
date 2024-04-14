#ifndef Cat_H
#define Cat_H

#include "constants.h"
#include <string>
#include <iostream>

class Cat
{
public:
    int catId;
    float x_position;
    float y_position;

    std::string catName;
    

    Cat(int characterId);
};

#endif // Cat_H
