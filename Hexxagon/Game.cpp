#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Field.h"
#include "Player.h"
#include "Enums.h"
#include "Constans.h"

class Game
{
private:
	sf::RenderWindow window;

	sf::Text text;

	sf::Font font;


public:
	std::vector<std::vector<Field>>myArray;

	std::vector<Player>listOfPlayer;

	std::vector<sf::Drawable*> objectsToDraw;

	int size;

	Game(int s, int countOfPlayer)
	{
		size = s;
		std::cout << "size: " << size << std::endl;
		std::cout << "countOfPlayer: " << countOfPlayer << std::endl;
		
		init();
	}

	void init()
	{
		if (!font.loadFromFile("../fonts/Tylko-Regular.ttf"))
		{
			sf::CircleShape* shape = new sf::CircleShape(100.f);
			shape->setFillColor(sf::Color::Green);
			objectsToDraw.push_back(shape);
		}
		createVec();
		fillVec();
        createListOfPlayer();
		renderWindow();
	}

	void renderWindow() {
		window.create(sf::VideoMode(1000, 1000), "SFML window");

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
					handleMouseClick(event.mouseButton.x, event.mouseButton.y);
				}
			}
			window.clear();
			drawButtons();
			window.display();
		}
	}

	void handleMouseClick(int x, int y) {
		sf::Text* clickText = new sf::Text("Mouse clicked at", font, 20);
		clickText->setFillColor(sf::Color::Green);
		clickText->setPosition(400.f, 10.f);
		objectsToDraw.push_back(clickText);
	}

	void drawButtons() {
		const float buttonSize = 50.f;  // размер кнопок
		const float rowSpacing = buttonSize * std::sqrt(4.f) / 2.f;  // расстояние между рядами кнопок
		const float colSpacing = buttonSize * 5.f / 2.f;  // расстояние между столбцами кнопок

		for (auto drawable : objectsToDraw) {
			window.draw(*drawable);
		}

		for (int row = 0; row < myArray.size(); ++row) {
			float x = 0;
			for (int col = 0; col < myArray[row].size(); ++col) {
				float y = (buttonSize + 10.f) * row;
				int space = buttonSize + rowSpacing;

				if (myArray[row].size() < size && col == 0) {
					x += space * (size - myArray[row].size());
				}
				else if (col > 0) {
					x += space * 2;
				}

				sf::RectangleShape button(sf::Vector2f(buttonSize, buttonSize));
				button.setPosition(x, y);
				button.setFillColor(sf::Color::Red);

				window.draw(button);
			}
		}

	}

	void createVec()
	{
		int horisontalSize = size;
		horisontalSize += (horisontalSize - 1);
		horisontalSize += horisontalSize;

		myArray.resize(horisontalSize);

		for (int i = 0; i < myArray.size(); i++) {

			if (i <= size)
			{
				myArray[i].resize(i);
			}
			else if (i < myArray.size() - size)
			{
				if (size % 2 == 0)
				{
					myArray[i].resize(i % 2 == 0 ? size : size - 1);
				}
				else
				{
					myArray[i].resize(i % 2 == 0 ? size - 1 : size);
				}
			}
			else
			{
				myArray[i].resize(myArray.size() - i);
			}
		}
		myArray.erase(myArray.begin());
	}

	void fillVec()
	{
		for (int i = 0; i < myArray.size(); i++)
		{
			for (int j = 0; j < myArray[i].size(); j++)
			{
				Field field(TypeOfField::EMPTY, false);
				myArray[i][j] = field;
			}
		}
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

	void print()
	{
		for (int i = 0; i < myArray.size(); i++)
		{
			for (int j = 0; j < myArray[i].size(); j++)
			{
				std::string space;

                if(myArray[i].size() < size && j == 0) {
                    space.append((size - myArray[i].size()) , ' ');
                }
                else if (j > 0) {
                    space.append(1, ' ');
                }
				std::cout << space << myArray[i][j].type;
			}
			std::cout << std::endl;
		}

		for (int i = 0; i < listOfPlayer.size(); i++)
		{
			std::cout << "Player: " << listOfPlayer[i].type << std::endl;
		}
	}
};