#include "fish.h"

Fish::Fish(int fishId)
{
    std::cout << "Fish Created" << std::endl;
    this->fishId = fishId;
    this->x_position = rand() % Constants::windowWidth;
    this->y_position = rand() % Constants::windowHeight;

    std::cout << "Fish Created, locate at " << this->x_position << "," << this->y_position << std::endl;

}

