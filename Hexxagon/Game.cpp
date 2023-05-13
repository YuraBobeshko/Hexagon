#pragma once

#include "Player.h"
#include "Board.h"
#include "Struct.h"
#include "Enums.h"


// newObjectsToDraw.emplace_back(log(elem->value, x, y));

class Game
{
private:
	sf::RenderWindow window;

	sf::Text text;

	MyFont font;

	std::vector<DrawableItem*> objectsToDraw;

	std::vector<Player*> listOfPlayer;
	
public:

	Game() {
		//Board game2(3, 2);
		//Board game3(4, 2);
		//Board game4(5, 2);
		//Board game5(6, 2);
		init();
	}

	void init()
	{
		Player* player1 = new Player(PLAYER1, PlayerTypes::REAL_PLAYER);
		Player* player2 = new Player(PLAYER2, PlayerTypes::BOT);
		listOfPlayer.emplace_back(player1);
		listOfPlayer.emplace_back(player2);
		createButtonsCountOfPlayer();
		renderWindow();
	}

	void renderWindow() {
		window.create(sf::VideoMode(SCREEN_SIZE_X, SCREEN_SIZE_Y), "Settings");

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

	void handleMouseClick(int x, int y) 
	{
		std::vector<DrawableItem*> newObjectsToDraw;

		for (auto* elem : objectsToDraw) {
			sf::FloatRect bounds = elem->item->getLocalBounds();
			sf::Transformable* transformable = dynamic_cast<sf::Transformable*>(elem->item);
			if (transformable != nullptr) {
				bounds.left += transformable->getPosition().x;
				bounds.top += transformable->getPosition().y;
			}
			if (bounds.contains(x, y)) {
				std::string identifier = elem->key;
				listOfPlayer.clear();
				if (identifier == "ñountOfPlayer") {
					handleClickOnCountOfUser(elem);
				}
				else if (identifier == "player") {
					std::string value = elem->value;
					int playerIndex = std::stoi(value.substr(value.length() - 1)) - 1;
					Player* player = listOfPlayer[playerIndex];
				}
			}
		}
		objectsToDraw.clear();

		objectsToDraw = newObjectsToDraw;
		renderAll();
	}

	void handleClickOnCountOfUser(DrawableItem* elem) {
		int value = std::stoi(elem->value);

		for (int i = 0; i < value; i++)
		{
			Player* player = new Player(TypeOfField(i + 1), PlayerTypes::BOT);
			listOfPlayer.emplace_back(player);
		}
	}

	void renderAll() {
		createButtonsCountOfPlayer();
		createButtonsListPlayer();

		for (auto drawable : objectsToDraw) {
			window.draw(*drawable->item);
		}
	}
	
	void createButtonsCountOfPlayer() {
		sf::Text* textCountOfPlayer = createText("Select count of player", TEXT_SIZE, 10, LINE_SIZE);
		sf::Text* textCountOfPlayer1 = createText("2", TEXT_SIZE, 10, LINE_SIZE * 2);
		sf::Text* textCountOfPlayer2 = createText("3", TEXT_SIZE, 35, LINE_SIZE * 2);
		sf::Text* textCountOfPlayer3 = createText("6", TEXT_SIZE, 60, LINE_SIZE * 2);

		objectsToDraw.emplace_back(new DrawableItem{ "textCountOfPlayer", NUMBER_OF_PLAYER, "textCountOfPlayer", textCountOfPlayer });
		objectsToDraw.emplace_back(new DrawableItem{ "ñountOfPlayer", NUMBER_OF_PLAYER,"2", textCountOfPlayer1 });
		objectsToDraw.emplace_back(new DrawableItem{ "ñountOfPlayer", NUMBER_OF_PLAYER, "3", textCountOfPlayer2 });
		objectsToDraw.emplace_back(new DrawableItem{ "ñountOfPlayer", NUMBER_OF_PLAYER, "6", textCountOfPlayer3 });
	}

	void createButtonsListPlayer() {
		sf::Text* textCountOfPlayer = createText("Number       Player       Bot", TEXT_SIZE, 10, LINE_SIZE * 3);


		objectsToDraw.emplace_back(new DrawableItem{ "textCountOfPlayer", TYPE_OF_PLAYER, "textCountOfPlayer", textCountOfPlayer });

		for (size_t i = 0; i < listOfPlayer.size(); i++)
		{

			std::string name = listOfPlayer[i]->getFieldName(listOfPlayer[i]->type);
				
			sf::Text* textOfPlayer = createText(name, TEXT_SIZE, 10, LINE_SIZE * (i + 4));
			
			objectsToDraw.emplace_back(new DrawableItem{ "player", TYPE_OF_PLAYER, "player" + i + 1, textOfPlayer });
		}
	}

	sf::Text* createText(std::string string, int size, int x, int y) {
		sf::Text* text = new sf::Text(string, font.get(), size);
		text->setFillColor(sf::Color::Green);
		text->setPosition(x, y);

		return text;
	}

	DrawableItem* log(std::string text, int x, int y) {
		sf::Text* clickText = new sf::Text("(" + std::to_string(x) + ", " + std::to_string(y) + ") " + text, font.get());
		clickText->setFillColor(sf::Color::Green);
		clickText->setPosition(400.f, 10.f);

		return new DrawableItem{ "log", NUMBER_OF_PLAYER, "log", clickText };
	}
};