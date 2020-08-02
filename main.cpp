/*
Tutorial Used: How To Make Games #7 : Entity Component System in C++ & SDL2 Tutorial
	URL: https://www.youtube.com/watch?v=XsvI8Sng6dk&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx
Comments are of my own writing, explains what does what so I can remember in the future (a.k.a. for reference)
*/

#include "Game.h"

Game* game = nullptr;

int main(int argc, const char* argv[])
{

	const int FPS = 60;//Framerate
	const int frameDelay = 1000 / FPS;//max time between frames

	Uint32 frameStart;//unsigned 32 bit integer
	int frameTime;

	game = new Game();
	
	game->initializeGame("Game Loop Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 640, false);

	while (game->running())//basically says while the game is actually running then do the stuff below
	{

		frameStart = SDL_GetTicks();
		
		game->handleEvents();
		game->update();
		game->render();

		frameTime = SDL_GetTicks() - frameStart;//basically subtracting the current SDL_GetTicks() from the previous one used to define frameStart

		if (frameDelay > frameTime)//if our Delay is still greater than the current frameTime then we need to delay it
		{
			SDL_Delay(frameDelay - frameTime);
		}
	}

	game->clean();

	return 0;
}