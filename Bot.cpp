#include "Bot.h"
#include <chrono>
#include <thread>

Bot::Bot(TypeOfField t, PlayerTypes p) :  Player(t, p) {}

bool Bot::makeAutoMove(std::vector<std::vector<Field *>> &map) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    std::vector<Position> ownPositions = getOwnPositions(map);
    MoveAnalytic move = findTheBestMove(ownPositions, map);

    Player::takePosition(move.selected, move.move, map);

    return true;
}

std::vector<Position> Bot::getOwnPositions(std::vector<std::vector<Field *>> &map) {
    std::vector<Position> moves;
    for (int i = 0; i < map.size(); ++i) {
        for (int j = 0; j < map[i].size(); ++j) {
            if(map[i][j]->type == Player::type) {
                moves.emplace_back(Position{i, j});
            }
        }
    }
    return moves;
}

MoveAnalytic Bot::findTheBestMove(std::vector<Position> &ownPositions, std::vector<std::vector<Field *>> &map) {
    std::vector<MoveAnalytic> listAnalyticMove;
    for (auto & move : ownPositions) {
        std::vector<MoveAnalytic> listPossibleMove;
        std::vector<Position> closedField = Player::getAllFields(move, map);

        for (auto & closedMove : closedField) {
            listAnalyticMove.emplace_back(getAnalyticForMove(closedMove, move, map));
        }

    }

    int theBiggestScore = -1;
    int theBiggestScoreIndex = 0;

    for (int i = 0; i < listAnalyticMove.size(); ++i) {
        if(listAnalyticMove[i].score > theBiggestScore) {
            theBiggestScore = listAnalyticMove[i].score;
            theBiggestScoreIndex = i;
        }
    }

    return listAnalyticMove[theBiggestScoreIndex];
}

MoveAnalytic Bot::getAnalyticForMove(Position &move, Position selected, std::vector<std::vector<Field *>> &map) {
    int score = 1;
    std::vector<Position> positions = Player::getCloseFields(move, map);
    for (auto & position : positions) {
        if(map[position.x][position.y]->type != Player::type &&
        map[position.x][position.y]->type != EMPTY &&
        map[position.x][position.y]->type != BLOCKED) {
            score++;
        }
    }
    return MoveAnalytic{selected, move, score};
}
