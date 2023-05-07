#include <iostream>
#include <vector>
#include "Field.h"
#include "Player.h"
#include "Enums.h"

class Game
{
public:
	std::vector<std::vector<Field>>myArray;

	std::vector<Player>listOfPlayer;

	int size;

	Game(int s, int countOfPlayer)
	{
		size = s;
		std::cout << "size: " << size << std::endl;
		std::cout << "countOfPlayer: " << countOfPlayer << std::endl;

		init();
	}

	void play()
	{
		std::cout << "play\n" << std::endl;
	}

	void init()
	{
		createVec();
		fillVec();
        createListOfPlayer();
        print();
		play();
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