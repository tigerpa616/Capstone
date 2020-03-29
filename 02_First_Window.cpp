//Using SDL and standard IO
#include <SDL.h> //We include SDL.h since we're going to need the SDL functions and datatypes to make any SDL code//   
#include <stdio.h>//We're including stdio.h so we can print errors to the console//

//Screen dimension constants
const int SCREEN_WIDTH = 640; //Declaring the Width of the window we are going to render//
const int SCREEN_HEIGHT = 480; //Declaring the Height of the window we are going to render//

int main(int argc, char* args[])//It's important that we have the arguments of the function be an integer followed by a char* array and the return type be an integer. Any other type of main function will cause an undefined reference to main//
{
	//The window we'll be rendering to
	SDL_Window* window = NULL; //Window we will render to//

	//The surface contained by the window
	SDL_Surface* screenSurface = NULL; //Actual screen surface//

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)//Initializes SDL. We need this so we can call SDL functions//
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}

	else
	{
		//Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}

		else
		{
			//Get window surface
			screenSurface = SDL_GetWindowSurface(window);

			//Fill the surface white
			SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0xFF, 0xFF, 0xFF));

			//Update the surface
			SDL_UpdateWindowSurface(window);

			//Wait two seconds
			SDL_Delay(2000000);
		}
	}

	//Destroy window
	SDL_DestroyWindow(window);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}