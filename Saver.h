#ifndef HEXAGON_SAVER_H
#define HEXAGON_SAVER_H

#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Font.h"
#include "Field.h"
#include "Player.h"

#include "Enums.h"
#include "Constants.h"
#include "Struct.h"

struct SavedGame {
    std::vector<Player> listOfPlayer;
    std::vector<std::vector<Field>> map;
};


class Saver {
    void saveGame(const std::vector<Player>& listOfPlayer, std::vector<std::vector<Field>> map) const;
    SavedGame resumeGame(int Id) const;
};


#endif //HEXAGON_SAVER_H
