#pragma once
#include "Game.h"

class Map
{
public:

	Map(); //Constructor for making the map
	~Map(); //Deconstructor for memory allocation

	void LoadMap(int array[20][25]); //Allows us to load a map
	void DrawMap(); //Allows us to draw a map

private:

	SDL_Rect source, destination; //Holds our source & destination for rendering
	SDL_Texture* dirt;
	SDL_Texture* grass;
	SDL_Texture* water;

	int map[20][25]; //something to actually hold the map
};
