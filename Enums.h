#ifndef ENUMS_H
#define ENUMS_H

#include <SFML/Graphics.hpp>

enum TypeOfField
{
    EMPTY,
    PLAYER1,
    PLAYER2,
    PLAYER3,
    PLAYER4,
    PLAYER5,
    PLAYER6,
    BLOCKED
};

enum ItemTypes
{
    NUMBER_OF_PLAYER,
    TYPE_OF_PLAYER,
};

enum PlayerTypes
{
    REAL_PLAYER,
    BOT,
};

enum TypesOfSelection
{
    UNSELECTED,
    SELECTED,
    POSSIBLE_TO_MOVE
};

#endif // ENUMS_H
