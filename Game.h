#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL.h>
#undef main //needed to avoid LNK2019 Error

class Game
{
public:
	Game();//Constructor to construct the Game object 
	~Game();//deconstructor for when we close it

	void initializeGame(const char* title, int x_position, int y_position, int width, int height, bool fullscreen); //method for initalizing the game

	void handleEvents();
	void update();//Where game will update all its positions
	void render();
	void clean();

	bool running() { return isRunning; }; //inline function that returns isRunning

private:
	int count = 0;
	bool isRunning;
	SDL_Window* window;
	SDL_Renderer* renderer;
};

#endif /* Game_hpp */