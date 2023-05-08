#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Field.h"
#include "Player.h"
#include "Font.h"

#include "Enums.h"
#include "Constans.h"

class Board
{
private:
	sf::RenderWindow window;

	sf::Text text;

	MyFont font;

	std::vector<std::vector<Field>>map;

	std::vector<Player>listOfPlayer;

	std::vector<sf::Drawable*> objectsToDraw;

	int size;

public:
	Board(int s, int countOfPlayer)
	{
		size = s;
		std::cout << "size: " << size << std::endl;
		std::cout << "countOfPlayer: " << countOfPlayer << std::endl;
		
		init();
	}

	void init()
	{
		createVec();
		fillVec();
        createListOfPlayer();
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
				Field field(TypeOfField::EMPTY, false);
				map[i][j] = field;
			}
		}

		int midX = size + size - 2;
		int midY = map[midX].size() / 2;

		Field field(TypeOfField::BLOCKED, false);
		map[midX-2][midY] = field;
		map[midX+1][midY] = field;
		map[midX + 1][midY + (size%2==0 ? +1 : -1)] = field;
	}

	void createListOfPlayer() {
		int count = 2;
		listOfPlayer.resize(count);
		for (int i = 0; i < count; i++)
		{
			Player player(TypeOfField(i + 1));
			listOfPlayer[i] = player;
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
		sf::Text* clickText = new sf::Text("Mouse clicked at (" + std::to_string(x) + ", " + std::to_string(y) + ")", font.get());
		clickText->setFillColor(sf::Color::Green);
		clickText->setPosition(400.f, 10.f);
		objectsToDraw.push_back(clickText);
	}

	void renderAll() {
		for (auto drawable : objectsToDraw) {
			window.draw(*drawable);
		}

		renderButtons();
		renderUsers();
	}

	void renderButtons() {
		const int rowSpacing = HEX_SIZE * std::sqrt(3) / 2;
		const int topSpace = SIZE_OF_USER_FIELD_STATE * listOfPlayer.size() + 30;
		
		for (auto drawable : objectsToDraw) {
			window.draw(*drawable);
		}

		for (int row = 0; row < map.size(); ++row) {
			float x = LEFT_SPACE;
			for (int col = 0; col < map[row].size(); ++col) {
				float y = HEX_SIZE * row + topSpace;
				int space = HEX_SIZE + rowSpacing;

				if (map[row].size() < size && col == 0) {
					x += space * (size - map[row].size());
				}
				else if (col > 0) {
					x += space * 2;
				}

				window.draw(map[row][col].render(x, y));
			}
		}

	}

	void renderUsers() {
		for (size_t i = 0; i < listOfPlayer.size(); i++)
		{
			window.draw(listOfPlayer[i].render());
		}
	}
};
