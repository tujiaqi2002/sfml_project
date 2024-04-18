#ifndef Fish_H
#define Fish_H

#include "constants.h"
#include <string>
#include <iostream>

class Fish
{
public:
    int fishId;
    float x_position;
    float y_position;

    std::string fishName;
    

    Fish(int fishId);
};

#endif // Cat_H
