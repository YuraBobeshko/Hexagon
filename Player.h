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
    bool makeMove(const Position p, std::vector<std::vector<Field*>>& map) const;
    static std::vector<Position> getCloseFields(const Position p, const std::vector<std::vector<Field*>>& map);
    static bool checkLocationInCloseFields(const Position p, const std::vector<Position>& closePositions);
    void takePosition(const Position mainP, const Position selected, std::vector<std::vector<Field*>>& map) const;
    static Position findMainP(std::vector<std::vector<Field*>>& map);
    static void selectPossibleMoves(const Position p, std::vector<std::vector<Field*>>& map) ;
    static int getYPosition(Position oldP, Position newP, const std::vector<std::vector<Field*>>& map) ;
    static Position getBottomPosition(Position oldP, const std::vector<std::vector<Field*>>& map) ;
    static Position getTopPosition(Position oldP, const std::vector<std::vector<Field*>>& map) ;
    static int getYRightBottomPosition(Position oldP, const std::vector<std::vector<Field*>>& map) ;
    static int getTopSidePosition(Position oldP, const std::vector<std::vector<Field*>>& map) ;
    static void unselect(std::vector<std::vector<Field*>>& map);
    static bool checkBounds(const std::vector<std::vector<Field*>>& vec, const Position p);
    static std::vector<Position> getSecondFields(const Position p, const std::vector<std::vector<Field *>> &map) ;

    static std::vector<Position> getAllFields(const Position p, const std::vector<std::vector<Field *>> &map);
};

#endif // MY_Player_H
