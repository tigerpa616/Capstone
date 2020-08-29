#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include <SDL.h>
#include "SDL_image.h"
#include <vector>
#undef main //needed to avoid LNK2019 Error

class ColliderComponent;

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

	static void AddTile(int sourceX, int sourceY, int xPosition, int yPosition);
	static SDL_Renderer* renderer;//used so we don't have to make multiple copies of the same pointer

	bool running() { return isRunning; }; //inline function that returns isRunning

	static SDL_Event event;
	static std::vector<ColliderComponent*> colliders;

private:
	int count = 0;
	bool isRunning;
	SDL_Window* window;
	//SDL_Renderer* rendererPrivate; No longer needed
};

#endif /* Game_hpp */