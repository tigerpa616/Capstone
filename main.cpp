#include "Game.h"

Game* game = nullptr;

int main(int argc, const char* argv[])
{
	game = new Game();
	
	game->initializeGame("Game Loop Test", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game->running())//basically says while the game is actually running then do the stuff below
	{
		game->handleEvents();
		game->update();
		game->render();
	}

	game->clean();

	return 0;
}