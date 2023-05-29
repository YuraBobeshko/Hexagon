#include "Player.h"

Player::Player(TypeOfField t, PlayerTypes p) {
    type = t;
    playerType = p;
}

sf::Text Player::render(const std::vector<std::vector<Field*>>& map) {
    sf::Text text(getFieldName(type) + " Score: " + std::to_string(getScore(map)), font.get(), FONT_SIZE_OF_USER_FIELD_STATE);
    text.setPosition(10.f, SIZE_OF_USER_FIELD_STATE * (type - 1));
    text.setFillColor(sf::Color::Red);

    return text;
}

std::string Player::getFieldName(TypeOfField field)
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

int Player::getScore(const std::vector<std::vector<Field*>>& map)
{
    int count = 0;
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j]->type == type) {
                count++;
            }
        }
    }

    return count;
}

bool Player::makeMove(Position p, std::vector<std::vector<Field*>>& map) {
    bool isNextPlayer = false;

    switch (map[p.x][p.y]->selection)
    {
    case UNSELECTED:
        unselect(map);
        map[p.x][p.y]->selection = SELECTED;
        selectPossibleMoves(p, map);
        break;
    case SELECTED:
        map[p.x][p.y]->selection = UNSELECTED;
        unselect(map);
        break;
    case POSSIBLE_TO_MOVE:
        isNextPlayer = true;
        map[p.x][p.y]->type = type;

        Position mainP = findMainP(map);

        std::vector<Position> closePosition = getCloseFields(mainP, map);

        if (!checkLocationInCloseFields(p, closePosition)) {
            map[mainP.x][mainP.y]->type = EMPTY;
        }

        takePosition(getCloseFields(p, map), map);

        unselect(map);
        break;
    }

    return isNextPlayer;
}

std::vector<Position> Player::getCloseFields(Position p, const std::vector<std::vector<Field*>>& map) {
    Position firstTop = Position{ p.x - 2, getYPosition(p, Position{p.x - 2, p.y}, map) };

    Position firstRightTop = Position{ p.x - 1 , getTopSidePosition(p, map) + 1 };
    Position firstLeftTop = Position{ p.x - 1, getTopSidePosition(p, map) };


    Position firstBottom = Position{ p.x + 2, getYPosition(p, Position{p.x + 2, p.y}, map) };

    Position firstRightBottom = Position{ p.x + 1 , getYRightBottomPosition(p, map) + 1 };
    Position firstLeftBottom = Position{ p.x + 1, getYRightBottomPosition(p, map) };

    std::vector<Position> moves = {
        firstTop,
        firstBottom,
        firstRightBottom, firstLeftBottom,
        firstRightTop, firstLeftTop,
    };

    return moves;
}

bool Player::checkLocationInCloseFields(Position p, std::vector<Position> closePositions) {
    for (int i = 0; i < closePositions.size(); i++)
    {
        Position currentP = closePositions[i];
        if (currentP.x == p.x && currentP.y == p.y) {
            return true;
        }
    }
    return false;
}

void Player::takePosition(std::vector<Position> positions, std::vector<std::vector<Field*>>& map) {
    for (int i = 0; i < positions.size(); i++)
    {
        Position p = positions[i];

        if (checkBounds(map, p) && !(map[p.x][p.y]->type == EMPTY) && !(map[p.x][p.y]->type == BLOCKED)) {
            map[p.x][p.y]->type = type;
        }
    }
}

Position Player::findMainP(std::vector<std::vector<Field*>>& map) {
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j]->selection == SELECTED) {
                return Position{ i, j };
            }
        }
    }

    return Position{ -1, -1 };
}

void Player::selectPossibleMoves(Position p, std::vector<std::vector<Field*>>& map) {
    Position firstRight = Position{ p.x , p.y + 1 };
    Position firstLeft = Position{ p.x , p.y - 1 };

    Position firstTop = Position{ p.x - 2, getYPosition(p, Position{p.x - 2, p.y}, map) };
    Position secondTop = Position{ p.x - 4, getYPosition(p, Position{p.x - 4, p.y}, map) };

    Position firstRightTop = Position{ p.x - 1 , getTopSidePosition(p, map) + 1 };
    Position firstLeftTop = Position{ p.x - 1, getTopSidePosition(p, map) };

    Position secondRightTop = getTopPosition(firstRightTop, map);
    Position secondLeftTop = getTopPosition(firstLeftTop, map);

    Position thirdRightTop = getTopPosition(firstRight, map);
    Position thirdLeftTop = getTopPosition(firstLeft, map);

    Position firstBottom = Position{ p.x + 2, getYPosition(p, Position{p.x + 2, p.y}, map) };
    Position secondBottom = Position{ p.x + 4, getYPosition(p, Position{p.x + 4, p.y}, map) };

    Position firstRightBottom = Position{ p.x + 1 , getYRightBottomPosition(p, map) + 1 };
    Position firstLeftBottom = Position{ p.x + 1, getYRightBottomPosition(p, map) };

    Position secondRightBottom = getBottomPosition(firstRightBottom, map);
    Position secondLeftBottom = getBottomPosition(firstLeftBottom, map);

    Position thirdRightBottom = getBottomPosition(firstRight, map);
    Position thirdLeftBottom = getBottomPosition(firstLeft, map);

    std::vector<Position> moves = {
        firstTop, secondTop,
        firstBottom, secondBottom,
        firstRight, firstLeft,
        firstRightBottom, firstLeftBottom,
        secondRightBottom, secondLeftBottom,
        thirdRightBottom, thirdLeftBottom,
        thirdRightTop, thirdLeftTop,
        firstRightTop, firstLeftTop,
        secondRightTop, secondLeftTop
    };

    for (size_t i = 0; i < moves.size(); i++)
    {
        if (checkBounds(map, moves[i])) {
            if (map[moves[i].x][moves[i].y]->type == EMPTY)
            {
                map[moves[i].x][moves[i].y]->selection = POSSIBLE_TO_MOVE;
            }
        }
    }
}

int Player::getYPosition(Position oldP, Position newP, const std::vector<std::vector<Field*>>& map) {
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

Position Player::getBottomPosition(Position oldP, std::vector<std::vector<Field*>>& map) {
    return Position{ oldP.x + 2, getYPosition(oldP, Position{oldP.x + 2, oldP.y}, map) };
}

Position Player::getTopPosition(Position oldP, std::vector<std::vector<Field*>>& map) {
    return Position{ oldP.x - 2, getYPosition(oldP, Position{oldP.x - 2, oldP.y}, map) };
}

int Player::getYRightBottomPosition(Position oldP, const std::vector<std::vector<Field*>>& map) {
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

int Player::getTopSidePosition(Position oldP, const std::vector<std::vector<Field*>>& map) {
    int size = 5;

    if (map[oldP.x].size() >= size)
    {
        return oldP.y - 1;
    }
    else
    {
        Position newP = Position{ oldP.x - 1, oldP.y };

        if (checkBounds(map, newP) && map[oldP.x].size() != size) {
            if (map[oldP.x].size() > map[newP.x].size()) {
                return oldP.y - 1;
            }
        }

        Position newPLower = Position{ oldP.x - 1, oldP.y - 1 };

        if (checkBounds(map, newPLower) && map[oldP.x].size() < map[newPLower.x].size()) {
            if (map[oldP.x].size() == (oldP.y - 1)) {
                return newPLower.y;
            }
        }

        return oldP.y;
    }
}

void Player::unselect(std::vector<std::vector<Field*>>& map) {
    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            Field* currentField = map[i][j];

            currentField->selection = UNSELECTED;
        }
    }
}

bool Player::checkBounds(const std::vector<std::vector<Field*>>& vec, Position p)
{
    if (p.x >= 0 && p.y >= 0 && p.x < vec.size() && p.y < vec[p.x].size()) {
        return true;
    }
    else {
        return false;
    }
}
