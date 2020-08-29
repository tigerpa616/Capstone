#include "Map.h"
#include "Game.h"
#include <fstream>//allows us to read our map externally

Map::Map()
{
}

Map::~Map()
{
}

void Map::LoadMap(std::string path, int sizeX, int sizeY) //the point of the array is so we can load a map
{
	char tile;
	std::fstream mapFile;
	mapFile.open(path);

	int sourceX, sourceY;

	for (int y = 0; y < sizeY; y++)
	{
		for (int x = 0; x < sizeX; x++)
		{
			mapFile.get(tile);
			sourceY = atoi(&tile) * 32;
			
			mapFile.get(tile);
			sourceX = atoi(&tile) * 32;

			Game::AddTile(sourceX, sourceY, x *64, y *64);
			mapFile.ignore();
		}
	}


	mapFile.close();
}

