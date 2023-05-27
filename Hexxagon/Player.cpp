#ifndef MY_Player_H
#define MY_Player_H
#include <iostream>
#include <cstdlib>

#include <SFML/Graphics.hpp>

#include "Font.h"
#include "Field.h"

#include "Enums.h"
#include "Constans.h"
#include "Struct.h"

class Player
{
public:
	TypeOfField type;

    PlayerTypes playerType;

	MyFont font;

    Player() : type(TypeOfField::EMPTY), playerType(PlayerTypes::BOT) {}

	Player(TypeOfField t, PlayerTypes p) {
		type = t;
        playerType = p;
	}

	sf::Text render() {
		sf::Text text(getFieldName(type), font.get(), FONT_SIZE_OF_USER_FIELD_STATE);
		text.setPosition(10.f, SIZE_OF_USER_FIELD_STATE * (type - 1));
		text.setFillColor(sf::Color::Red);

		return text;
	}

   static std::string getFieldName(TypeOfField field)
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

   void makeMove(Position p, std::vector<std::vector<Field*>>& map) {
       switch (map[p.x][p.y]->selection)
       {
       case UNSELECTED:
           unselect(map);
           selectPossibleMoves(p, map);
           break;
       case SELECTED:
           map[p.x][p.y]->selection = UNSELECTED;
           break;
       case POSSIBLE_TO_MOVE:
           break;
       default:
           break;
       }
   }

   void selectPossibleMoves(Position p, std::vector<std::vector<Field*>>& map) {
       //map[p.x][p.y]->selection = SELECTED;
       //map[p.x][p.y]->createHexagon();

       map[p.x][p.y]->type = EMPTY;

       Position firstTop = Position{ p.x - 2, getYPosition(p, Position{p.x - 2, p.y}, map) };
       Position secondTop = Position{ p.x - 4, getYPosition(p, Position{p.x - 4, p.y}, map) };

       Position firstBottom = Position{ p.x + 2, getYPosition(p, Position{p.x + 2, p.y}, map) };
       Position secondBottom = Position{ p.x + 4, getYPosition(p, Position{p.x + 4, p.y}, map) };

       Position firstRight = Position{ p.x , p.y + 1 };
       Position firstLeft = Position{ p.x , p.y - 1 };

       Position firstRightBottom = Position{ p.x + 1 , getYRightBottomPosition(p, map) + 1 };
       Position firstLeftBottom = Position{ p.x + 1, getYRightBottomPosition(p, map) };

       //Position secondRightBottom = Position{ firstRightBottom.x + 2 , getYPosition(firstRightBottom, Position{firstRightBottom.x + 2, firstRightBottom.y}, map) };
       Position secondRightBottom = getYBottomPosition(firstRightBottom, map);
       Position secondLeftBottom = Position{ firstRightBottom.x + 2, getYPosition(firstLeftBottom, Position{firstLeftBottom.x + 2, firstLeftBottom.y}, map) };


       std::vector<Position> moves = { 
           //firstBottom, secondBottom, 
           //firstTop, secondTop, 
           //firstRight, firstLeft, 
           //firstRightBottom, firstLeftBottom 
           secondRightBottom, //secondLeftBottom
       };

       for (size_t i = 0; i < moves.size(); i++)
       {
           if (checkBounds(map, moves[i])) {
               if (map[moves[i].x][moves[i].y]->type == EMPTY)
               {
                   map[moves[i].x][moves[i].y]->selection = SELECTED;
               }
           }
       }
   }

   int getYPosition(Position oldP, Position newP, std::vector<std::vector<Field*>>& map) {

       if (!checkBounds(map, newP)) {
           Position updatedP = Position{ newP.x, newP.y - 1 };

           if (!checkBounds(map, updatedP))
           {
               return -1;
           }

           newP = updatedP;
       }

       if (oldP.x == 0 && oldP.y == 0 || map.size() == oldP.x + 1) {
           int add = abs(newP.x - oldP.x) / 2;
           return oldP.y + add;
       }
       else if (map[oldP.x].size() == map[newP.x].size())
       {
           return oldP.y;
       }
       else if (map[oldP.x].size() < map[newP.x].size())
       {
           return oldP.y + 1;
       }
       else if (map[oldP.x].size() > map[newP.x].size())
       {
           return oldP.y - 1;
       }
       else
       {
           return -1;
       }

   }

   Position getYBottomPosition(Position oldP, std::vector<std::vector<Field*>>& map) {
       return Position{ oldP.x + 2 , getYPosition(oldP, Position{oldP.x + 2, oldP.y}, map) };
   }

   int getYRightBottomPosition(Position oldP, std::vector<std::vector<Field*>>& map) {
       int size = 5;

       if (map[oldP.x].size() >= size)
       {
           return oldP.y - 1;
       }
       else
       {
           Position newP = Position{ oldP.x + 1, oldP.y };

           if (checkBounds(map, newP) && map[oldP.x].size() != size) {
               if (map[oldP.x].size() > map[newP.x].size()) {
                   return oldP.y - 1;
               }
           }

           Position newPLower = Position{ oldP.x + 1, oldP.y - 1 };

           if (checkBounds(map, newPLower) && map[oldP.x].size() > map[newPLower.x].size()) {
               if (map[oldP.x].size() == (oldP.y + 1)) {
                   return newPLower.y;
               }
           }

           return oldP.y;
       }
   }

   void unselect(std::vector<std::vector<Field*>>& map) {
       for (size_t i = 0; i < map.size(); ++i) {
           for (size_t j = 0; j < map[i].size(); ++j) { 
               Field* currentField = map[i][j]; 

               currentField->selection = UNSELECTED;
           }
       }
   }

   bool checkBounds(const std::vector<std::vector<Field*>>& vec, Position p)
   {
       if (p.x >= 0 && p.y >= 0 && p.x < vec.size() && p.y < vec[p.x].size()) {
           return true;
       }
       else {
           return false;
       }
   }

};

#endif // MY_ENUMS_H
