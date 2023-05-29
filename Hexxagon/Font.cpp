#include "Font.h"

MyFont::MyFont()
{
    if (!font.loadFromFile("../fonts/Tylko-Regular.ttf")) {
        // Handle font loading error
    }
}

sf::Font& MyFont::get()
{
    return font;
}
