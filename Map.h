#pragma once
#include <string>


class Map
{
public:

	Map(); //Constructor for making the map
	~Map(); //Deconstructor for memory allocation

	static void LoadMap(std::string path, int sizeX, int sizeY); //Allows us to load a map
	//void DrawMap(); //Allows us to draw a map

private:

	//No longer needed due to AddTile() method
	//SDL_Rect source, destination; //Holds our source & destination for rendering
	//SDL_Texture* dirt;
	//SDL_Texture* grass;
	//SDL_Texture* water;
	//int map[20][25]; //something to actually hold the map
};
