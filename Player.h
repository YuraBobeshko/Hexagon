#ifndef MY_Player_H
#define MY_Player_H
#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Font.h"
#include "Field.h"

#include "Enums.h"
#include "Constants.h"
#include "Struct.h"

class Player
{
public:
    TypeOfField type;
    PlayerTypes playerType;
    MyFont font;

    Player() : type(TypeOfField::EMPTY), playerType(PlayerTypes::BOT) {}
    Player(TypeOfField t, PlayerTypes p);

    sf::Text render(const std::vector<std::vector<Field*>>& map);
    static std::string getFieldName(TypeOfField field);
    int getScore(const std::vector<std::vector<Field*>>& map) const;
    bool makeMove(Position p, std::vector<std::vector<Field*>>& map);
    std::vector<Position> getCloseFields(Position p, const std::vector<std::vector<Field*>>& map);
    static bool checkLocationInCloseFields(Position p, const std::vector<Position>& closePositions);
    void takePosition(std::vector<Position> positions, std::vector<std::vector<Field*>>& map);
    static Position findMainP(std::vector<std::vector<Field*>>& map);
    void selectPossibleMoves(Position p, std::vector<std::vector<Field*>>& map);
    int getYPosition(Position oldP, Position newP, const std::vector<std::vector<Field*>>& map);
    Position getBottomPosition(Position oldP, std::vector<std::vector<Field*>>& map);
    Position getTopPosition(Position oldP, std::vector<std::vector<Field*>>& map);
    int getYRightBottomPosition(Position oldP, const std::vector<std::vector<Field*>>& map);
    int getTopSidePosition(Position oldP, const std::vector<std::vector<Field*>>& map);
    static void unselect(std::vector<std::vector<Field*>>& map);
    static bool checkBounds(const std::vector<std::vector<Field*>>& vec, Position p);
};

#endif // MY_Player_H
