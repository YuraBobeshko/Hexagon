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

int Player::getScore(const std::vector<std::vector<Field*>>& map) const
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

bool Player::makeMove(Position p, std::vector<std::vector<Field*>>& map) const {
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
        takePosition(findMainP(map), p, map);

        unselect(map);
        break;
    }

    return isNextPlayer;
}

std::vector<Position> Player::getCloseFields(const Position p, const std::vector<std::vector<Field*>>& map) {
    auto firstTop = Position{ p.x - 2, getYPosition(p, Position{p.x - 2, p.y}, map) };

    auto firstRightTop = Position{ p.x - 1 , getTopSidePosition(p, map) + 1 };
    auto firstLeftTop = Position{ p.x - 1, getTopSidePosition(p, map) };


    auto firstBottom = Position{ p.x + 2, getYPosition(p, Position{p.x + 2, p.y}, map) };

    auto firstRightBottom = Position{ p.x + 1 , getYRightBottomPosition(p, map) + 1 };
    auto firstLeftBottom = Position{ p.x + 1, getYRightBottomPosition(p, map) };

    std::vector<Position> moves = {
        firstTop,
        firstBottom,
        firstRightBottom, firstLeftBottom,
        firstRightTop, firstLeftTop,
    };

    std::vector<Position> validMoves;

    for (auto & move : moves) {
        if(checkBounds(map, move)){
            validMoves.emplace_back(move);
        }
    }

    return validMoves;
}

std::vector<Position> Player::getSecondFields(const Position p, const std::vector<std::vector<Field*>>& map) {
    auto firstRight = Position{ p.x , p.y + 1 };
    auto firstLeft = Position{ p.x , p.y - 1 };

    auto secondTop = Position{ p.x - 4, getYPosition(p, Position{p.x - 4, p.y}, map) };

    auto firstRightTop = Position{ p.x - 1 , getTopSidePosition(p, map) + 1 };
    auto firstLeftTop = Position{ p.x - 1, getTopSidePosition(p, map) };

    auto secondRightTop = getTopPosition(firstRightTop, map);
    auto secondLeftTop = getTopPosition(firstLeftTop, map);

    auto thirdRightTop = getTopPosition(firstRight, map);
    auto thirdLeftTop = getTopPosition(firstLeft, map);

    auto secondBottom = Position{ p.x + 4, getYPosition(p, Position{p.x + 4, p.y}, map) };

    auto firstRightBottom = Position{ p.x + 1 , getYRightBottomPosition(p, map) + 1 };
    auto firstLeftBottom = Position{ p.x + 1, getYRightBottomPosition(p, map) };

    auto secondRightBottom = getBottomPosition(firstRightBottom, map);
    auto secondLeftBottom = getBottomPosition(firstLeftBottom, map);

    auto thirdRightBottom = getBottomPosition(firstRight, map);
    auto thirdLeftBottom = getBottomPosition(firstLeft, map);

    std::vector<Position> moves = {
            secondTop,
            secondBottom,
            firstRight, firstLeft,
            secondRightBottom, secondLeftBottom,
            secondRightTop, secondLeftTop,
            thirdRightBottom, thirdLeftBottom,
            thirdRightTop, thirdLeftTop
    };

    std::vector<Position> validMoves;

    for (auto & move : moves) {
        if(checkBounds(map, move)){
            validMoves.emplace_back(move);
        }
    }

    return validMoves;
}

std::vector<Position> Player::getAllFields(const Position p, const std::vector<std::vector<Field*>>& map) {
    std::vector<Position> moves;
    std::vector<Position> closeFields = getCloseFields(p, map);
    std::vector<Position> secondFields = getSecondFields(p, map);

    moves.reserve(closeFields.size() + secondFields.size());
    moves.insert(moves.end(), closeFields.begin(), closeFields.end());
    moves.insert(moves.end(), secondFields.begin(), secondFields.end());

    return moves;
}

bool Player::checkLocationInCloseFields(const Position p, const std::vector<Position>& closePositions) {
    for (auto currentP : closePositions)
    {
        if (currentP.x == p.x && currentP.y == p.y) {
            return true;
        }
    }
    return false;
}

void Player::takePosition(const Position mainP, const Position selected, std::vector<std::vector<Field*>>& map) const {
    std::vector<Position> closePosition = getCloseFields(mainP, map);

    map[selected.x][selected.y]->type = type;

    if (!checkLocationInCloseFields(selected, closePosition)) {
        map[mainP.x][mainP.y]->type = EMPTY;
    }
    for (auto p : getCloseFields(selected, map))
    {
        if (checkBounds(map, p) && map[p.x][p.y]->type != EMPTY && map[p.x][p.y]->type != BLOCKED) {
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

void Player::selectPossibleMoves(const Position p, std::vector<std::vector<Field*>>& map) {
    std::vector<Position> moves = getAllFields(p, map);

    for (auto & move : moves)
    {
        if (checkBounds(map, move)) {
            if (map[move.x][move.y]->type == EMPTY)
            {
                map[move.x][move.y]->selection = POSSIBLE_TO_MOVE;
            }
        }
    }
}

int Player::getYPosition(const Position oldP, Position newP, const std::vector<std::vector<Field*>>& map) {
    if (!checkBounds(map, newP)) {
        auto updatedP = Position{ newP.x, newP.y - 1 };

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

Position Player::getBottomPosition(const Position oldP, const std::vector<std::vector<Field*>>& map) {
    return Position{ oldP.x + 2, getYPosition(oldP, Position{oldP.x + 2, oldP.y}, map) };
}

Position Player::getTopPosition(const Position oldP, const std::vector<std::vector<Field*>>& map) {
    return Position{ oldP.x - 2, getYPosition(oldP, Position{oldP.x - 2, oldP.y}, map) };
}

int Player::getYRightBottomPosition(const Position oldP, const std::vector<std::vector<Field*>>& map) {
    int size = 5;

    if (map[oldP.x].size() >= size)
    {
        return oldP.y - 1;
    }
    else
    {
        auto newP = Position{ oldP.x + 1, oldP.y };

        if (checkBounds(map, newP) && map[oldP.x].size() != size) {
            if (map[oldP.x].size() > map[newP.x].size()) {
                return oldP.y - 1;
            }
        }

        auto newPLower = Position{ oldP.x + 1, oldP.y - 1 };

        if (checkBounds(map, newPLower) && map[oldP.x].size() > map[newPLower.x].size()) {
            if (map[oldP.x].size() == (oldP.y + 1)) {
                return newPLower.y;
            }
        }

        return oldP.y;
    }
}

int Player::getTopSidePosition(const Position oldP, const std::vector<std::vector<Field*>>& map) {
    int size = 5;

    if (map[oldP.x].size() >= size)
    {
        return oldP.y - 1;
    }
    else
    {
        auto newP = Position{ oldP.x - 1, oldP.y };

        if (checkBounds(map, newP) && map[oldP.x].size() != size) {
            if (map[oldP.x].size() > map[newP.x].size()) {
                return oldP.y - 1;
            }
        }

        auto newPLower = Position{ oldP.x - 1, oldP.y - 1 };

        if (checkBounds(map, newPLower) && map[oldP.x].size() < map[newPLower.x].size()) {
            if (map[oldP.x].size() == (oldP.y - 1)) {
                return newPLower.y;
            }
        }

        return oldP.y;
    }
}

void Player::unselect(std::vector<std::vector<Field*>>& map) {
    for (auto & i : map) {
        for (size_t j = 0; j < i.size(); ++j) {
            Field* currentField = i[j];

            currentField->selection = UNSELECTED;
        }
    }
}

bool Player::checkBounds(const std::vector<std::vector<Field*>>& vec, const Position p)
{
    if (p.x >= 0 && p.y >= 0 && p.x < vec.size() && p.y < vec[p.x].size()) {
        return true;
    }
    else {
        return false;
    }
}
