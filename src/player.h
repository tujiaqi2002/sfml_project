#ifndef PLAYER_H
#define PLAYER_H

#include "constants.h"
#include <string>
#include <iostream>

class Player
{
public:
    int playerId;
    std::string playerName;

    Player(int playerId);
};

#endif // PLAYER_H
