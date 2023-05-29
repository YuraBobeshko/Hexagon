#include "Field.h"

Field::Field() : type(TypeOfField::EMPTY), selection(TypesOfSelection::UNSELECTED), item(nullptr) {}

Field::Field(TypeOfField t, TypesOfSelection s) : type(t), selection(s), item(nullptr) {}

std::string Field::getName() {
    return std::to_string(static_cast<int>(type));
}

sf::ConvexShape* Field::render(int x, int y) {
    item = createHexagon();
    item->setPosition(x, y);
    return item;
}

sf::ConvexShape* Field::createHexagon() {
    sf::ConvexShape* hexagon = new sf::ConvexShape(6);
    hexagon->setPoint(0, sf::Vector2f(HEX_SIZE, 0));
    hexagon->setPoint(1, sf::Vector2f(HEX_SIZE / 2, HEX_HEIGHT / 2));
    hexagon->setPoint(2, sf::Vector2f(-HEX_SIZE / 2, HEX_HEIGHT / 2));
    hexagon->setPoint(3, sf::Vector2f(-HEX_SIZE, 0));
    hexagon->setPoint(4, sf::Vector2f(-HEX_SIZE / 2, -HEX_HEIGHT / 2));
    hexagon->setPoint(5, sf::Vector2f(HEX_SIZE / 2, -HEX_HEIGHT / 2));
    hexagon->setFillColor(getColor());
    hexagon->setOutlineThickness(5.f);
    hexagon->setOutlineColor(getColorForOutline());
    return hexagon;
}

sf::Color Field::getColor() {
    return getColor(type);
}

sf::Color Field::getColor(TypeOfField type) {
    switch (type) {
    case TypeOfField::EMPTY:
        return sf::Color::White;
    case TypeOfField::PLAYER1:
        return sf::Color::Red;
    case TypeOfField::PLAYER2:
        return sf::Color::Blue;
    case TypeOfField::PLAYER3:
        return sf::Color::Green;
    case TypeOfField::PLAYER4:
        return sf::Color::Yellow;
    case TypeOfField::PLAYER5:
        return sf::Color::Magenta;
    case TypeOfField::PLAYER6:
        return sf::Color::Cyan;
    case TypeOfField::BLOCKED:
        return sf::Color::Black;
    default:
        return sf::Color::Red;
    }
}

sf::Color Field::getColorForOutline() {
    switch (selection) {
    case TypesOfSelection::UNSELECTED:
        return sf::Color::Black;
    case TypesOfSelection::POSSIBLE_TO_MOVE:
        return sf::Color::Green;
    case TypesOfSelection::SELECTED:
        return sf::Color::Blue;
    default:
        return sf::Color::Black;
    }
}
