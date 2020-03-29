/*
Tutorial Used: How To Make A Game #2 : Drawing Textures/Sprites To The Screen : C++ And SDL2 Image Tutorial & How To Make a Game #3 : Limiting Frame Rate : C++ And SDL2 Tutorial
	URL: https://www.youtube.com/watch?v=YrWQsuDT3NE&t=1s & https://www.youtube.com/watch?v=jzasDqPmtPI
Comments are of my own writing, explains what does what so I can remember in the future (a.k.a. for reference)
*/

#include "Game.h"
#include <iostream>

SDL_Texture* playerTexture;//Creates a texture that will be used later to be a moving image
SDL_Rect sourceRectangle, destinationRectangle;//allows us to determine position of the playerTexture

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
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);//red,green,blue,black
			std::cout << "Renderer Created!" << std::endl;
		}

		isRunning = true;
	}

	SDL_Surface* temporarySurface = IMG_Load("assets/testimage.png");//creates a value that loads the png file
	playerTexture = SDL_CreateTextureFromSurface(renderer, temporarySurface);//uses the loaded png file and the renderer to create a texture
	SDL_FreeSurface(temporarySurface);//frees up the memory

	
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
	count++;//Everytime game gets updated counter increases
	
	destinationRectangle.h = 512;//changes the height of the destinationRectangle to 32 bits
	destinationRectangle.w = 512;//changes the width of the destinationRectangle to 32 bits
	destinationRectangle.x = count;//sets the image location on the x plane to be what ever the count value is
	destinationRectangle.y = count/2;//sets the image location on the y plane to be what ever half the count value is

	std::cout << count << std::endl;
}

void Game::render()
{
	SDL_RenderClear(renderer);
		
	SDL_RenderCopy(renderer, playerTexture, NULL, &destinationRectangle);//copys the render so it can be used

	SDL_RenderPresent(renderer);
}

void Game::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	std::cout << "Game Clean" << std::endl;
}

