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

    int targetFishId;

    std::string catName;
    

    Cat(int catId);
};

#endif // Cat_H
