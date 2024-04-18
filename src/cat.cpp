#include "cat.h"

Cat::Cat(int catId)
{
    std::cout << "Cat Created" << std::endl;
    this->catId = catId;
    this->x_position = rand() % Constants::windowWidth;
    this->y_position = rand() % Constants::windowHeight;

    std::cout << "Cat Created, locate at " << this->x_position << "," << this->y_position << std::endl;

}


