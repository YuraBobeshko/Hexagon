#include <string> 
#include "Enums.h"


class Field
{
public:
    TypeOfField type;
    bool selected;
    Field() : type(TypeOfField::EMPTY), selected(false) {}
    Field(TypeOfField t, bool s)
    {
        type = t;
        selected = s;
	}
    std::string getName() {
        if (selected) {
            return "[" + std::to_string(type) + "]";
        }
        else {
            return " " + std::to_string(type) + " ";
        }
    }
};

