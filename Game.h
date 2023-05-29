#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.h"
#include "Board.h"
#include "Struct.h"
#include "Enums.h"

class Game
{
private:
    sf::RenderWindow window;
    sf::Text text;
    MyFont font;
    std::vector<DrawableItem*> objectsToDraw;
    std::vector<Player*> listOfPlayer;

public:
    Game();
    void init();
    void renderWindow();
    void handleMouseClick(int x, int y);
    void handleClickOnCountOfUser(DrawableItem* elem);
    void handleClickOnUser(DrawableItem* elem);
    void processEvents();
    void renderFrame();
    void handleClickOnPlay();
    void renderAll();
    void createButtonsCountOfPlayer();
    void createButtonsListPlayer();
    void createButtonsPlay();
    sf::Text* createText(const std::string& string, int size, int x, int y);
};

#endif // GAME_H
