#ifndef STRUCT_H
#define STRUCT_H


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

#endif // STRUCT_H
