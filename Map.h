#pragma once
#include <string>


class Map
{
public:

	Map(std::string tID, int ms, int ts); //Constructor for making the map
	~Map(); //Deconstructor for memory allocation

	void LoadMap(std::string path, int sizeX, int sizeY); //Allows us to load a map
	void AddTile(int sourceX, int sourceY, int xPosition, int yPosition);
	//void DrawMap(); //Allows us to draw a map

private:

	std::string textureID;
	int mapScale;
	int tileSize;
	int scaledSize;
};
