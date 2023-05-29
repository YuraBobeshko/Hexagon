#include "Board.h"

Board::Board(int s, std::vector<Player*> l)
{
    size = s;
    listOfPlayer = l;
    std::cout << "size: " << size << std::endl;
    std::cout << "countOfPlayer: " << l.size() << std::endl;

    init();
}

void Board::init()
{
    createVec();
    fillVec();
    renderWindow();
}

void Board::createVec()
{
    int horisontalSize = size;
    horisontalSize += (horisontalSize - 1);
    horisontalSize += horisontalSize;

    map.resize(horisontalSize);

    for (int i = 0; i < map.size(); i++) {

        if (i <= size)
        {
            map[i].resize(i);
        }
        else if (i < map.size() - size)
        {
            if (size % 2 == 0)
            {
                map[i].resize(i % 2 == 0 ? size : size - 1);
            }
            else
            {
                map[i].resize(i % 2 == 0 ? size - 1 : size);
            }
        }
        else
        {
            map[i].resize(map.size() - i);
        }
    }
    map.erase(map.begin());
}

void Board::fillVec()
{
    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            Field* field = new Field(TypeOfField::EMPTY, UNSELECTED);
            map[i][j] = field;
        }
    }

    setEmptyVec();
    setPlayersVec();
}

void Board::setEmptyVec()
{
    int midX = size + size - 2;
    int midY = map[midX].size() / 2;

    Field* field = new Field(BLOCKED, UNSELECTED);
    map[midX - 2][midY] = field;
    map[midX + 1][midY] = field;
    map[midX + 1][midY + (size % 2 == 0 ? +1 : -1)] = field;
}

void Board::setPlayersVec()
{
    int realSize = size - 1;

    int horisontalSize = size;
    horisontalSize += (horisontalSize - 1);
    horisontalSize += horisontalSize;

    int playerID = 0;

    std::vector<Position> listPosition = {
        Position{0, 0},
        Position{realSize, 0},
        Position{realSize, realSize},
        Position{realSize * 3, 0},
        Position{realSize * 3, realSize},
        Position{horisontalSize - 2, 0},
    };

    for (int i = 0; i < listPosition.size(); i++)
    {
        Position position = listPosition[i];
        if (listOfPlayer.size() <= playerID) {
            playerID = 0;
        }
        map[position.x][position.y]->type = listOfPlayer[playerID]->type;
        playerID++;
    }
}

void Board::renderWindow() {
    window.create(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "SFML window");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2i clickPosition = sf::Mouse::getPosition(window);
                handleMouseClick(event.mouseButton.x, event.mouseButton.y);
            }
        }
        window.clear();
        renderAll();
        window.display();
    }
}

void Board::handleMouseClick(int x, int y) {
    objectsToDraw.clear();

    for (int i = 0; i < map.size(); ++i) {
        std::vector<Field*> elem = map[i];
        for (int j = 0; j < elem.size(); ++j) {
            Field* item = elem[j];
            sf::FloatRect bounds = item->item->getLocalBounds();
            sf::Transformable* transformable = dynamic_cast<sf::Transformable*>(item->item);
            if (transformable != nullptr) {
                bounds.left += transformable->getPosition().x;
                bounds.top += transformable->getPosition().y;
            }
            if (bounds.contains(x, y)) {
                handleClickOnField(item, i, j);
            }
        }
    }

    renderAll();
}

void Board::handleClickOnField(Field* item, int x, int y)
{
    Player* player = listOfPlayer[activePlayer];

    if (player->type == item->type || item->selection == POSSIBLE_TO_MOVE)
    {
        Position pos = Position{ x, y };

        if (player->makeMove(pos, map)) {
            nextPlayer();
        }

        sf::Text* clickText = new sf::Text(std::to_string(x) + "  " + std::to_string(y) + " " + map[x][y]->getName(), font.get());
        clickText->setFillColor(sf::Color::Green);
        clickText->setPosition(400.f, 10.f);
        objectsToDraw.push_back(clickText);
    }
}

void Board::nextPlayer() {
    if (activePlayer + 1 >= listOfPlayer.size()) {
        activePlayer = 0;
    }
    else {
        activePlayer++;
    }
}

void Board::renderAll()
{
    int winnerId = checkWinner();
    if (winnerId != -1) {
        window.draw(listOfPlayer[winnerId]->render(map));
        return;
    }

    renderButtons();
    renderUsers();

    for (auto drawable : objectsToDraw)
    {
        window.draw(*drawable);
    }
}

void Board::renderButtons()
{
    const int rowSpacing = HEX_SIZE * std::sqrt(3) / 2;
    const int topSpace = SIZE_OF_USER_FIELD_STATE * listOfPlayer.size() + 30;

    for (int row = 0; row < map.size(); ++row)
    {
        float x = LEFT_SPACE;
        for (int col = 0; col < map[row].size(); ++col)
        {
            float y = HEX_SIZE * row + topSpace;
            int space = HEX_SIZE + rowSpacing;

            if (map[row].size() < size && col == 0)
            {
                x += space * (size - map[row].size());
            }
            else if (col > 0)
            {
                x += space * 2;
            }
            window.draw(*map[row][col]->render(x, y));
        }
    }
}

void Board::renderUsers()
{
    for (int i = 0; i < listOfPlayer.size(); i++)
    {
        if (listOfPlayer[i]->getScore(map) != 0) {
            window.draw(listOfPlayer[i]->render(map));
        }
    }
}

int Board::checkWinner() {
    int userId = -1;
    int emptyFields = 0;

    std::vector<Player*> exsitingPlayer;

    for (int i = 0; i < map.size(); i++)
    {
        for (int j = 0; j < map[i].size(); j++)
        {
            if (map[i][j]->type == EMPTY) {
                emptyFields++;
                break;
            }
        }
    }

    if (emptyFields == 0) {
        int maxFields = 0;

        for (int i = 0; i < listOfPlayer.size(); i++)
        {
            if (maxFields < listOfPlayer[i]->getScore(map)) {
                maxFields = listOfPlayer[i]->getScore(map);
                userId = i;
            }
        }

        return userId;
    }

    for (int i = 0; i < listOfPlayer.size(); i++)
    {
        if (listOfPlayer[i]->getScore(map) != 0) {
            exsitingPlayer.emplace_back(listOfPlayer[i]);
            userId = i;
        }
    }

    if (exsitingPlayer.size() == 1) {
        return userId;
    }

    return -1;
}
