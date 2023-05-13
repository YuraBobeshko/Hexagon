#ifndef MY_ENUMS_H
#define MY_ENUMS_H

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

#endif // MY_ENUMS_H
