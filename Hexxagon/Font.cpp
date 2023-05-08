#include <SFML/Graphics.hpp>

class MyFont
{
public:
    sf::Font font;

    MyFont() {
        if (!font.loadFromFile("../fonts/Tylko-Regular.ttf")) {
            // Обработка ошибки загрузки шрифта
        }
    }

    sf::Font& get() {
        return font;
    }

private:
};





