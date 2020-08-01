#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include <iostream>
#include "Map.h"

//Don't need the below commented out code anymore thanks to GameObject.cpp/.h
//SDL_Texture* playerTexture;//Creates a texture that will be used later to be a moving image
//SDL_Rect sourceRectangle, destinationRectangle;//allows us to determine position of the playerTexture

GameObject* player;
GameObject* boss;
Map* map;

SDL_Renderer* Game::renderer = nullptr;//we have it set to nullptr because we haven't initialized SDL yet

Game::Game()
{}
Game::~Game()
{}

void Game::initializeGame(const char* title, int x_position, int y_position, int width, int height, bool fullscreen)
{
	int fullscreen_detector = 0;//workaround to get bool fullscreen working in SDL_CreateWindow, same with if statement below
	if (fullscreen)//if fullscreen is true then flags equal SDL_WINDOW_FULLSCREEN
	{
		fullscreen_detector = SDL_WINDOW_FULLSCREEN;//basically if fullscreen is true then the window becomes fullscreen
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) //IF THIS RETURNS 0 THEN THE SDL SYSTEMS HAVE BEEN PROPERLY INITIALIZED
	{
		std::cout << "Subsystems Initialized" << std::endl;

		window = SDL_CreateWindow(title, x_position, y_position, width, height, fullscreen_detector);
		if (window)
		{
			std::cout << "Window Created!" << std::endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);//*FIGURE OUT HOW THIS WORKS*//
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 0, 255, 0, 0);//red,green,blue,black
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}

	//Don't need the below commented out code anymore thanks to TextureManager.cpp/.h
	//SDL_Surface* temporarySurface = IMG_Load("assets/testimage.png");//creates a value that loads the png file
	//playerTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);//uses the loaded png file and the renderer to create a texture
	//SDL_FreeSurface(temporarySurface);//frees up the memory

	//playerTexture = TextureManager::LoadTexture("assets/testimage.png", renderer);
	player = new GameObject("assets/player.png", 0, 0);
	boss = new GameObject("assets/boss.png", 100, 100);
	map = new Map();


}

void Game::handleEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)//switch statement to check the form of event happening, duh
	{
	case SDL_QUIT://event.SDL_QUIT means that you want to quit the event, dumbass
		isRunning = false;
		break;
	default://default case, if you don't know what that means at this point you should kill yourself Dylan Driscoll
		break;
	}
}

void Game::update()
{
	player->Update();//updates the player
	boss->Update();//updates the boss

	//Everything below has been replaced thanks to GameObject.cpp/.h
	//count++;//Everytime game gets updated counter increases
	//destinationRectangle.h = 512;//changes the height of the destinationRectangle to 32 bits
	//destinationRectangle.w = 512;//changes the width of the destinationRectangle to 32 bits
	//destinationRectangle.x = count;//sets the image location on the x plane to be what ever the count value is
	//destinationRectangle.y = count/2;//sets the image location on the y plane to be what ever half the count value is
	//std::cout << count << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);

	map->DrawMap();

	player->Render();
	boss->Render();

	//Everything below has been replaced thanks to GameObject.cpp/.h
	//SDL_RenderCopy(renderer, playerTexture, NULL, &destinationRectangle);//copys the render so it can be used

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Clean" << std::endl;
}

