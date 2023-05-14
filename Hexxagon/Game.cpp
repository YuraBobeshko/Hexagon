#pragma once
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

	Game() : listOfPlayer({ new Player(TypeOfField(1), REAL_PLAYER), new Player(TypeOfField(2), BOT) }) {
		init();
	}

	void init()
	{
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
				
				if (identifier == "ñountOfPlayer") {
					handleClickOnCountOfUser(elem);
					break;
				}
				else if (identifier == "player") {
					handleClickOnUser(elem);
					break;
				}
				else if (identifier == "Play") {
					handleClickOnPlay();
					break;
				}
			}
		}
		objectsToDraw.clear();

		objectsToDraw = newObjectsToDraw;
		renderAll();
	}

	void handleClickOnCountOfUser(DrawableItem* elem) {
		int value = std::stoi(elem->value);
		
		if (listOfPlayer.size() == value)
			return;

		listOfPlayer.resize(value);

		for (int i = 0; i < listOfPlayer.size(); i++)
		{
			Player* player = new Player(TypeOfField(i + 1), i == 0 ? REAL_PLAYER : BOT);
			listOfPlayer[i] = player;
		}
	}

	void handleClickOnUser(DrawableItem* elem) {
		int playerIndex = std::stoi(elem->value) - 1;

		Player* player = listOfPlayer[playerIndex];

		listOfPlayer[playerIndex] = new Player(player->type, player->playerType == BOT ? REAL_PLAYER : BOT);
	}

	void handleClickOnPlay() {
		window.close();

		Board board(5, listOfPlayer);
	}

	void renderAll() {
		createButtonsCountOfPlayer();
		createButtonsListPlayer();
		createButtonsPlay();

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
		sf::Text* textCountOfPlayer = createText("Number      type", TEXT_SIZE, 10, LINE_SIZE * 3);

		objectsToDraw.emplace_back(new DrawableItem{ "textCountOfPlayer", TYPE_OF_PLAYER, "textCountOfPlayer", textCountOfPlayer });

		if (listOfPlayer.size() == 0)
			return;

		for (int i = 0; i < listOfPlayer.size(); i++)
		{
			if (!listOfPlayer[i])
				return;

			std::string name = listOfPlayer[i]->getFieldName(listOfPlayer[i]->type);
			std::string type = listOfPlayer[i]->playerType == PlayerTypes::REAL_PLAYER ? "User" : "Bot";

			sf::Text* textOfPlayer = createText(name + "       " + type, TEXT_SIZE, 10, LINE_SIZE * (i + 4));

			objectsToDraw.emplace_back(new DrawableItem{ "player", TYPE_OF_PLAYER, std::to_string(1 + i), textOfPlayer });
		}
	}

	void createButtonsPlay() {
		sf::Text* textCountOfPlayer = createText("PLAY", TEXT_SIZE, 10, 0);

		objectsToDraw.emplace_back(new DrawableItem{ "Play", TYPE_OF_PLAYER, "Play", textCountOfPlayer });
	}

	sf::Text* createText(std::string string, int size, int x, int y) {
		sf::Text* text = new sf::Text(string, font.get(), size);
		text->setFillColor(sf::Color::Green);
		text->setPosition(x, y);

		return text;
	}
};