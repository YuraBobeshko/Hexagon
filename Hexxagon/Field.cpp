#include <string> 

#include <SFML/Graphics.hpp>

#include "Enums.h"
#include "Constans.h"


class Field
{
public:
    TypeOfField type;
    bool selected;
    Field() : type(TypeOfField::EMPTY), selected(false) {}

    Field(TypeOfField t, bool s)
    {
        type = t;
        selected = s;
    }

    std::string getName() {
        if (selected) {
            return "[" + std::to_string(type) + "]";
        }
        else {
            return "" + std::to_string(type) + "";
        }
    }

    sf::ConvexShape render(int x, int y) {
        return createHexagon(x, y);
    }

    sf::ConvexShape createHexagon(float x, float y) {
        sf::ConvexShape hexagon(6);
        hexagon.setPoint(0, sf::Vector2f(HEX_SIZE, 0));
        hexagon.setPoint(1, sf::Vector2f(HEX_SIZE / 2, HEX_HEIGHT / 2));
        hexagon.setPoint(2, sf::Vector2f(-HEX_SIZE / 2, HEX_HEIGHT / 2));
        hexagon.setPoint(3, sf::Vector2f(-HEX_SIZE, 0));
        hexagon.setPoint(4, sf::Vector2f(-HEX_SIZE / 2, -HEX_HEIGHT / 2));
        hexagon.setPoint(5, sf::Vector2f(HEX_SIZE / 2, -HEX_HEIGHT / 2));
        hexagon.setPosition(x, y);
        hexagon.setFillColor(getColor(type));

        return hexagon;
    }

    sf::Color getColor(TypeOfField type) {
        switch (type) {
        case EMPTY:
            return sf::Color::White;
        case PLAYER1:
            return sf::Color::Red;
        case PLAYER2:
            return sf::Color::Blue;
        case PLAYER3:
            return sf::Color::Green;
        case PLAYER4:
            return sf::Color::Yellow;
        case PLAYER5:
            return sf::Color::Magenta;
        case PLAYER6:
            return sf::Color::Cyan;
        case BLOCKED:
            return sf::Color::Black;
        default:
            return sf::Color::White;
        }
    }
};

