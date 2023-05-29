#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "Field.h"
#include "Player.h"
#include "Font.h"
#include "Enums.h"
#include "Constants.h"
#include "Struct.h"

class Board
{
private:
    sf::RenderWindow window;
    sf::Text text;
    MyFont font;
    std::vector<std::vector<Field*>> map;
    std::vector<Player*> listOfPlayer;
    std::vector<sf::Drawable*> objectsToDraw;
    int size;
    int activePlayer = 0;

public:
    Board(int s, std::vector<Player*> l);
    void init();
    void createVec();
    void fillVec();
    void setEmptyVec();
    void setPlayersVec();
    void renderWindow();
    void handleMouseClick(int x, int y);
    void handleClickOnField(Field* item, int x, int y);
    void nextPlayer();
    void renderAll();
    void renderButtons();
    void renderUsers();
    int checkWinner();
};

#endif // BOARD_H
