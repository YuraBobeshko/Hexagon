#ifndef DRAWABLEITEM_H
#define DRAWABLEITEM_H

#include <SFML/Graphics.hpp>
#include "Enums.h"

struct DrawableItem
{
    std::string key;
    ItemTypes type;
    std::string value;
    sf::Text* item;
};

struct Position
{
    int x;
    int y;
};

#endif // DRAWABLEITEM_H
