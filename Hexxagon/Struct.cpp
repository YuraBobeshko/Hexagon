#ifndef MY_DrawableItem_H
#define MY_DrawableItem_H

#include <SFML/Graphics.hpp>

#include "Enums.h"

struct DrawableItem
{
	std::string key;
	ItemTypes type;
	std::string value;
	sf::Text* item;
};

#endif // MY_ENUMS_H
