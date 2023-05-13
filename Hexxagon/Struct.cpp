#include <SFML/Graphics.hpp>


#include "Enums.h"

struct DrawableItem
{
	std::string key;
	ItemTypes type;
	std::string value;
	sf::Text* item;
};
