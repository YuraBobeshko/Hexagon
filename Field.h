#ifndef FIELD_H
#define FIELD_H

#include <string>
#include <SFML/Graphics.hpp>
#include "Enums.h"
#include "Constants.h"

class Field
{
public:
    TypeOfField type;
    TypesOfSelection selection;
    sf::ConvexShape* item;

    Field();
    Field(TypeOfField t, TypesOfSelection s);
    std::string getName() const;
    sf::ConvexShape* render(int x, int y);

    static sf::Color getColor(TypeOfField type);
    sf::Color getColor() const;
    sf::Color getColorForOutline() const;

private:
    sf::ConvexShape* createHexagon();
};

#endif // FIELD_H
