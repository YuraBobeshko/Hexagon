#include <SFML/Graphics.hpp>

#include "Font.h"

#include "Enums.h"
#include "Constans.h"

class Player
{
public:
	TypeOfField type;

	MyFont font;

    Player() : type(TypeOfField::EMPTY) {}

	Player(TypeOfField t) {
		type = t;
	}

	sf::Text render() {
		sf::Text text(getFieldName(type), font.get(), FONT_SIZE_OF_USER_FIELD_STATE);
		text.setPosition(10.f, SIZE_OF_USER_FIELD_STATE * (type - 1));
		text.setFillColor(sf::Color::Red);

		return text;
	}

    std::string getFieldName(TypeOfField field)
    {
        switch (field)
        {
        case PLAYER1:
            return "Player 1";
        case PLAYER2:
            return "Player 2";
        case PLAYER3:
            return "Player 3";
        case PLAYER4:
            return "Player 4";
        case PLAYER5:
            return "Player 5";
        case PLAYER6:
            return "Player 6";
        default:
            return "Unknown";
        }
    }
};

