#ifndef HEXAGON_SAVER_H
#define HEXAGON_SAVER_H

#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Player.h"

#include "Enums.h"
#include "Struct.h"


class Bot : public Player {

    std::vector<Position> getOwnPositions(std::vector<std::vector<Field*>>& map);
    MoveAnalytic findTheBestMove(std::vector<Position>& ownPositions, std::vector<std::vector<Field*>>& map);
    MoveAnalytic getAnalyticForMove(Position& move, Position selected, std::vector<std::vector<Field*>>& map);

public:
    Bot(TypeOfField t, PlayerTypes p);

    bool makeAutoMove(std::vector<std::vector<Field*>>& map);
};


#endif //HEXAGON_SAVER_H
