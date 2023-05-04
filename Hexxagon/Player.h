#include "Enums.h"

class Player
{
public:
	TypeOfField type;
	Player(TypeOfField t) {
		type = t;
	}
	Player() : type(TypeOfField::EMPTY) {}
};

