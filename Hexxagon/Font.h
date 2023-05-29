#ifndef FONT_H
#define FONT_H

#include <SFML/Graphics.hpp>

class MyFont
{
public:
    sf::Font font;

    MyFont();

    sf::Font& get();
};

#endif // FONT_H
