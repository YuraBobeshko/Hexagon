#ifndef BOARD
#define BOARD

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Field.h"
#include "Player.h"
#include "Font.h"

#include "Enums.h"
#include "Constans.h"
#include "Struct.h"

class Board
{
private:
	sf::RenderWindow window;

	sf::Text text;

	MyFont font;

	std::vector<std::vector<Field*>> map;

	std::vector<Player*> listOfPlayer;

	std::vector<sf::Drawable*> objectsToDraw;

	int size;

public:
	Board(int s, std::vector<Player*> l)
	{
		size = s;
		listOfPlayer = l;
		std::cout << "size: " << size << std::endl;
		std::cout << "countOfPlayer: " << l.size() << std::endl;

		init();
	}

	void init()
	{
		createVec();
		fillVec();
		renderWindow();
	}

	void createVec()
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

	void fillVec()
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

	void setEmptyVec()
	{
		int midX = size + size - 2;
		int midY = map[midX].size() / 2;

		Field* field = new Field(BLOCKED, UNSELECTED);
		map[midX - 2][midY] = field;
		map[midX + 1][midY] = field;
		map[midX + 1][midY + (size % 2 == 0 ? +1 : -1)] = field;
	}

	void setPlayersVec()
	{
		switch (listOfPlayer.size())
		{
		case 2:
			map[0][0] = new Field(TypeOfField::PLAYER1, UNSELECTED);
			map[size - 1][0] = new Field(TypeOfField::PLAYER1, UNSELECTED);
			map[size - 1][map[size - 1].size() - 1] = new Field(TypeOfField::PLAYER2, UNSELECTED);
			break;

		case 3:

			break;

		case 6:

			break;

		default:
			break;
		}
	}

	void renderWindow() {
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

	void handleMouseClick(int x, int y) {
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

	void handleClickOnField(Field* item, int x, int y)
	{
		map[x][y]->type = PLAYER1;

		for (Player* player : listOfPlayer)
		{
			if (player->type == item->type)
			{
				Position pos = Position{ x, y };

				player->makeMove(pos, map);

				sf::Text* clickText = new sf::Text(std::to_string(x) + "  " + std::to_string(y), font.get());
				clickText->setFillColor(sf::Color::Green);
				clickText->setPosition(400.f, 10.f);
				objectsToDraw.push_back(clickText);
				
			}
		}
	}

	void renderAll()
	{
		renderButtons();
		renderUsers();

		for (auto drawable : objectsToDraw)
		{
			window.draw(*drawable);
		}
	}

	void renderButtons()
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

	void renderUsers()
	{
		for (size_t i = 0; i < listOfPlayer.size(); i++)
		{
			window.draw(listOfPlayer[i]->render());
		}
	}
};

#endif