#include "cat.h"

Cat::Cat(int catId)
{
    std::cout << "Cat Created" << std::endl;
    this->catId = catId;
    this->x_position = rand();
    this->y_position = rand();
}
