#include <iostream>

class Game
{ 

public:
	std::string** myArray;
	int size;
	void play() 
	{
		std::cout << "play" << std::endl;
	}
	void init()
	{
		myArray = new std::string * [size * 3];
		for (int i = 0; i < size * 3; i++) {
			myArray[i] = new std::string[size];
			for (int j = 0; j < size; j++) {
				myArray[i][j] = (i + j) % 2 == 0 ? " 0 " : "   ";
			}
		}
		print();
	}

	void print() {
		std::cout << "print" << std::endl;
		for (int i = 0; i < size * 3; i++)
		{
			for (int j = 0; j < size; j++) {
				std::cout << myArray[i][j] << " ";
			}
			std::cout << std::endl;
		}
	}
	Game(int s, int countOfPlayer)
	{
		size = s;
		std::cout << "size: " << s << "\ncountOfPlayer: " << countOfPlayer << std::endl;
		init();
	}
	~Game() 
	{
		for (int i = 0; i < size; i++) {
			delete[] myArray[i];
		}
		delete[] myArray;
	}
};

