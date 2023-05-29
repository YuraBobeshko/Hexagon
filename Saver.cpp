//
// Created by gorob on 29.05.2023.
//

#include <fstream>
#include "Saver.h"


void Saver::saveGame(const std::vector<Player>& listOfPlayer, std::vector<std::vector<Field>> map) const {
//    std::ofstream outFile("../savings/savings.txt");
//    for (const auto& row : map) {
//        for (const auto& field_ptr : row) {
//            outFile << static_cast<int>(field_ptr.type) << " " << static_cast<int>(field_ptr.selection) << " " << static_cast<int>(field_ptr.position) << " ";
//        }
//        outFile << '\n';
//    }
//    outFile.close();
}

SavedGame Saver::resumeGame(int Id) const {
    return {};
}
