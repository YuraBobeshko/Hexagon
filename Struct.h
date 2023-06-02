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

struct MoveAnalytic
{
    Position selected;
    Position move;
    int score;
};


#endif // STRUCT_H
